#include "aj_mainui.h"
#include <GUI/ngui.h>
#include <gameapp.h>
#include "FSM/fsm.h"
#include "FSM/aj_endlessgame.h"
#include "FSM/aj_gameui.h"
#include "aj_input.h"

AJ_MainUI::AJ_MainUI()
{

}

bool AJ_MainUI::onEnter()
{
    using namespace CEGUI;
    WindowManager& winMgr = WindowManager::getSingleton();
    winMgr.destroyAllWindows();
    Window* guiRoot = winMgr.loadLayoutFromFile( "AJ_MainUI.layout" );
    System::getSingleton().getDefaultGUIContext().setRootWindow( guiRoot );
    guiRoot->getChild("FrameWindow/Story")->subscribeEvent(CEGUI::Window::EventMouseClick,Event::Subscriber(&AJ_MainUI::buttonStory));
    guiRoot->getChild("FrameWindow/Endless")->subscribeEvent(CEGUI::Window::EventMouseClick,Event::Subscriber(&AJ_MainUI::buttonEndless));
    guiRoot->getChild("FrameWindow/Quit")->subscribeEvent(CEGUI::Window::EventMouseClick,Event::Subscriber(&AJ_MainUI::buttonQuit));
    return true;
}

bool AJ_MainUI::onExit()
{
    using namespace CEGUI;
    WindowManager& winMgr = WindowManager::getSingleton();
    winMgr.destroyAllWindows();
    return true;
}

void AJ_MainUI::update()
{
    AJ_Input::the()->update();
}

string AJ_MainUI::getStateID()
{
    return string("mainUI");
}

bool AJ_MainUI::injectKeyDown(int keyCode)
{
    return false;
}

bool AJ_MainUI::injectKeyUp(int keyCode)
{
    return false;
}

void AJ_MainUI::buttonStory(const CEGUI::EventArgs &)
{

}

void AJ_MainUI::buttonEndless(const CEGUI::EventArgs &)
{
    FSM::the()->add(new AJ_EndlessGame);
    FSM::the()->changeState(new AJ_GameUI);
}

void AJ_MainUI::buttonQuit(const CEGUI::EventArgs &)
{
    cout <<__FUNCTION__<<endl;
    GameApp::the()->isRuning = false;
}
