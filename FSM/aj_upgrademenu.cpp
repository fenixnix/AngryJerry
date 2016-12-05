#include "aj_upgrademenu.h"
#include "aj_input.h"
#include "FSM/fsm.h"
#include "global.h"
#include "aj_avatar.h"

AJ_UpgradeMenu::AJ_UpgradeMenu()
{

}

void AJ_UpgradeMenu::setButtonList(vector<string> bl)
{
  buttonList = bl;
}

bool AJ_UpgradeMenu::onEnter()
{
  using namespace CEGUI;
  WindowManager& winMgr = WindowManager::getSingleton();
  winMgr.destroyAllWindows();
  Window* guiRoot = winMgr.loadLayoutFromFile( "AJ_Upgrade.layout" );
  System::getSingleton().getDefaultGUIContext().setRootWindow( guiRoot );
  if(buttonList.size()>=1){
      guiRoot->getChild("FrameWindow/Button1")->setText(buttonList[0]);
      guiRoot->getChild("FrameWindow/Button1")->subscribeEvent(CEGUI::Window::EventMouseClick,Event::Subscriber(&AJ_UpgradeMenu::buttonButton));
      guiRoot->getChild("FrameWindow/Button1")->subscribeEvent(CEGUI::Window::EventMouseEntersArea,Event::Subscriber(&AJ_UpgradeMenu::buttonInfo));
    }
  if(buttonList.size()>=2){
      guiRoot->getChild("FrameWindow/Button2")->setText(buttonList[1]);
      guiRoot->getChild("FrameWindow/Button2")->subscribeEvent(CEGUI::Window::EventMouseClick,Event::Subscriber(&AJ_UpgradeMenu::buttonButton));
      guiRoot->getChild("FrameWindow/Button2")->subscribeEvent(CEGUI::Window::EventMouseEntersArea,Event::Subscriber(&AJ_UpgradeMenu::buttonInfo));
    }
  if(buttonList.size()>=3){
      guiRoot->getChild("FrameWindow/Button3")->setText(buttonList[2]);
      guiRoot->getChild("FrameWindow/Button3")->subscribeEvent(CEGUI::Window::EventMouseClick,Event::Subscriber(&AJ_UpgradeMenu::buttonButton));
      guiRoot->getChild("FrameWindow/Button3")->subscribeEvent(CEGUI::Window::EventMouseEntersArea,Event::Subscriber(&AJ_UpgradeMenu::buttonInfo));
    }
  guiRoot->getChild("FrameWindow")->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked,Event::Subscriber(&AJ_UpgradeMenu::buttonCancel));
  return true;
}

bool AJ_UpgradeMenu::onExit()
{
  using namespace CEGUI;
  WindowManager& winMgr = WindowManager::getSingleton();
  winMgr.destroyAllWindows();
  return true;
}

void AJ_UpgradeMenu::update()
{
  AJ_Input::the()->update();
}

string AJ_UpgradeMenu::getStateID()
{
  return "upgradeMenu";
}

void AJ_UpgradeMenu::buttonButton(const CEGUI::EventArgs &evt)
{
  using namespace CEGUI;
  const WindowEventArgs& wea = static_cast<const WindowEventArgs&>(evt);
  string skillID = string( wea.window->getText().c_str());
  cout<<__FUNCTION__<<":"<<skillID<<endl;
  Global::the()->techTree.setTech(skillID);
  AJ_Avatar::the()->costSkillPoint(skillID);
  FSM::the()->popState();
}

void AJ_UpgradeMenu::buttonInfo(const CEGUI::EventArgs &evt)
{
  using namespace CEGUI;
  const WindowEventArgs& wea = static_cast<const WindowEventArgs&>(evt);
  string skillID = string( wea.window->getText().c_str());
  string info = Global::the()->techTree.getTechInfo(skillID);
  Window* guiRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
  guiRoot->getChild("FrameWindow/Label")->setText(info);
}

void AJ_UpgradeMenu::buttonCancel(const CEGUI::EventArgs &)
{
  FSM::the()->popState();
}
