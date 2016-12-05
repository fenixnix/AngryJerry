#ifndef AJ_GAMEMENU_H
#define AJ_GAMEMENU_H

#include "FSM/stateuibase.h"

class AJ_GameMenu : public StateUIBase
{
public:
    AJ_GameMenu();
    bool onEnter();
    bool onExit();
    void update();
    std::string getStateID();
    static void buttonResume(const CEGUI::EventArgs&);
    static void buttonQuit(const CEGUI::EventArgs&);
};

#endif // AJ_GAMEMENU_H
