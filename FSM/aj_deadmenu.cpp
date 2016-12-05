#include "aj_deadmenu.h"
#include "aj_input.h"
#include "FSM/fsm.h"
#include "FSM/aj_mainui.h"

AJ_DeadMenu::AJ_DeadMenu()
{

}

bool AJ_DeadMenu::onEnter()
{
    using namespace CEGUI;
    WindowManager& winMgr = WindowManager::getSingleton();
    winMgr.destroyAllWindows();
    Window* guiRoot = winMgr.loadLayoutFromFile( "AJ_DeadMenu.layout" );
    System::getSingleton().getDefaultGUIContext().setRootWindow( guiRoot );
    guiRoot->getChild("FrameWindow/OK")->subscribeEvent(CEGUI::Window::EventMouseClick,Event::Subscriber(&AJ_DeadMenu::buttonOK));
    return true;
}

bool AJ_DeadMenu::onExit()
{
    using namespace CEGUI;
    WindowManager& winMgr = WindowManager::getSingleton();
    winMgr.destroyAllWindows();
    return true;
}

void AJ_DeadMenu::update()
{
    AJ_Input::the()->update();
}

string AJ_DeadMenu::getStateID()
{
    return string("deadMenu");
}

void AJ_DeadMenu::buttonOK(const CEGUI::EventArgs &)
{
    FSM::the()->delAll();
    FSM::the()->popState();
    FSM::the()->changeState(new AJ_MainUI);
}
