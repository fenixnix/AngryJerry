#include "aj_gameui.h"
#include "aj_input.h"
#include "aj_avatar.h"
#include "Render/nglrender.h"
#include "FSM/fsm.h"
#include "FSM/aj_gamemenu.h"
#include "objmngr.h"
#include "FSM/aj_deadmenu.h"
#include "global.h"
#include "FSM/aj_upgrademenu.h"
#include "nfmodmngr.h"

FMOD::Studio::EventInstance* fmodBGM;

AJ_GameUI::AJ_GameUI()
{
  lk = false;
  rk = false;
  mouseLb = false;
  mouseRb = false;
}

bool AJ_GameUI::onEnter()
{
  using namespace CEGUI;
  WindowManager& winMgr = WindowManager::getSingleton();
  winMgr.destroyAllWindows();
  Window* guiRoot = winMgr.loadLayoutFromFile( "AJ_GameUI.layout" );
  System::getSingleton().getDefaultGUIContext().setRootWindow( guiRoot );
  //guiRoot->getChild("FrameWindow/Resume")->subscribeEvent(CEGUI::Window::EventMouseClick,Event::Subscriber(&AJ_GameMenu::buttonResume));
  //guiRoot->getChild("FrameWindow/Quit")->subscribeEvent(CEGUI::Window::EventMouseClick,Event::Subscriber(&AJ_GameMenu::buttonQuit));
  NFMODMngr::the()->getEventPrefab("Music:Basic:Random Layered")->createInstance(&fmodBGM);
  fmodBGM->start();
  return true;
}

bool AJ_GameUI::onExit()
{
  fmodBGM->stop(FMOD_STUDIO_STOP_IMMEDIATE);
  NFMODMngr::the()->getEventPrefab("Music:Basic:Random Layered")->releaseAllInstances();
  return true;
}

void AJ_GameUI::update()
{
  AJ_Input::the()->update();
  if(lk){
      AJ_Avatar::the()->force(-2,0);
    }
  if(rk){
      AJ_Avatar::the()->force(2,0);
    }
  if(mouseRb){
      AJ_Avatar::the()->charge();
    }
  if(mouseLb){
      AJ_Avatar::the()->shoot1(mx,my);
    }
  if(!ObjMngr::the()->has(AJ_Avatar::the()->avatarID)){
      FSM::the()->pushState(new AJ_DeadMenu);
    }
  AJ_Avatar::the()->update();
  NFMODMngr::the()->update();
}

void AJ_GameUI::render()
{
  using namespace CEGUI;
  WindowManager& winMgr = WindowManager::getSingleton();
  Window* guiRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
  int avdID = AJ_Avatar::the()->avatarID;
  if(ObjMngr::the()->has(avdID)){
      Obj* obj = ObjMngr::the()->getObj(avdID);
      if(obj->isUnit()){
          Unit* unit = dynamic_cast<Unit*>(obj);
          float x = unit->phyxBody->GetTransform().p.x;
          ostringstream os;
          os<<"Level:"<<AJ_Avatar::the()->lvExp.getLevel()<<" ";
          os<<"SkillPoint:"<<AJ_Avatar::the()->getSkillPoint()<<" ";
          os<<"Meter:"<<x<<" ";

          guiRoot->getChild("X")->setText(os.str());

          os.str("");
          os<<"FPS:"<<Global::the()->fps<<" ";
          guiRoot->getChild("FPS")->setText(os.str());

          ostringstream osLife;
          osLife<<(float)unit->hp/(float)unit->maxHp;
          guiRoot->getChild("Life")->setProperty("CurrentProgress",osLife.str());

          ostringstream osAmmo;
          osAmmo<<AJ_Avatar::the()->getAmmoPercent();
          guiRoot->getChild("Ammo")->setProperty("CurrentProgress",osAmmo.str());

          ostringstream osPower;
          osPower<<AJ_Avatar::the()->getPower();
          guiRoot->getChild("Charge")->setProperty("CurrentProgress",osPower.str());

          ostringstream osExp;
          osExp<<AJ_Avatar::the()->lvExp.expPercent2LevelUp();
          guiRoot->getChild("Exp")->setProperty("CurrentProgress",osExp.str());

        }
    }
  NGUI::the()->draw();
}

bool AJ_GameUI::injectKeyDown(int keyCode)
{
  if(keyCode == SDL_SCANCODE_A){
      lk = true;
    }
  if(keyCode == SDL_SCANCODE_D){
      rk = true;
    }
  if(keyCode == SDL_SCANCODE_F10){
      Global::the()->isDrawDebug = !Global::the()->isDrawDebug;
    }
  if(keyCode == SDL_SCANCODE_SPACE){
      AJ_Avatar::the()->jump();
    }
  if(keyCode == SDL_SCANCODE_W){
      AJ_Avatar::the()->jump();
    }
  if(keyCode == SDL_SCANCODE_UP){
      AJ_Avatar::the()->jump();
    }
  if(keyCode == SDL_SCANCODE_U){
      if(AJ_Avatar::the()->canUpgrade()){
          vector<string > skills = Global::the()->techTree.getRandomReachableTech(3);
          if(skills.empty()){
              return true;
            }
          AJ_UpgradeMenu* ajMenu = new AJ_UpgradeMenu;
          ajMenu->setButtonList(skills);
          FSM::the()->pushState(ajMenu);
        }
    }

  if(lk^rk){

    }

  if(keyCode == SDL_SCANCODE_ESCAPE){
      FSM::the()->pushState(new AJ_GameMenu);
    }
  return true;
}

bool AJ_GameUI::injectKeyUp(int keyCode)
{
  //cout<<__FUNCTION__<<endl;
  if(keyCode == SDL_SCANCODE_A){
      lk = false;
    }
  if(keyCode == SDL_SCANCODE_D){
      rk = false;
    }
  return true;
}

bool AJ_GameUI::injectMouseRightDown()
{
  mouseRb = true;
  return true;
}

bool AJ_GameUI::injectMouseRightUp()
{
  mouseRb = false;
  NGLRender::the()->getMousePos(mx,my,mz);
  AJ_Avatar::the()->shoot(mx,my);
  return true;
}

bool AJ_GameUI::injectMouseLeftDown()
{
  //cout<<__FUNCTION__<<endl;
  mouseLb = true;
  return true;
}

bool AJ_GameUI::injectMouseLeftUp()
{
  mouseLb = false;
  return true;
}
