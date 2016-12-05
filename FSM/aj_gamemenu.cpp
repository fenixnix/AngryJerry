#include "aj_gamemenu.h"
#include "aj_input.h"
#include "FSM/fsm.h"
#include "FSM/aj_mainui.h"

AJ_GameMenu::AJ_GameMenu()
{

}

bool AJ_GameMenu::onEnter()
{
    using namespace CEGUI;
    WindowManager& winMgr = WindowManager::getSingleton();
    winMgr.destroyAllWindows();
    Window* guiRoot = winMgr.loadLayoutFromFile( "AJ_GameMenu.layout" );
    System::getSingleton().getDefaultGUIContext().setRootWindow( guiRoot );
    guiRoot->getChild("FrameWindow/Resume")->subscribeEvent(CEGUI::Window::EventMouseClick,Event::Subscriber(&AJ_GameMenu::buttonResume));
    guiRoot->getChild("FrameWindow/Quit")->subscribeEvent(CEGUI::Window::EventMouseClick,Event::Subscriber(&AJ_GameMenu::buttonQuit));
    return true;
}

bool AJ_GameMenu::onExit()
{
    using namespace CEGUI;
    WindowManager& winMgr = WindowManager::getSingleton();
    winMgr.destroyAllWindows();
    return true;
}

void AJ_GameMenu::update()
{
    AJ_Input::the()->update();
}

string AJ_GameMenu::getStateID()
{
    return string("gameMenu");
}

void AJ_GameMenu::buttonResume(const CEGUI::EventArgs &)
{
    FSM::the()->popState();
}

void AJ_GameMenu::buttonQuit(const CEGUI::EventArgs &)
{
    FSM::the()->delAll();
    FSM::the()->popState();
    FSM::the()->pushState(new AJ_MainUI);
}
