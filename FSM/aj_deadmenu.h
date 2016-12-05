#ifndef AJ_DEADMENU_H
#define AJ_DEADMENU_H

#include "FSM/stateuibase.h"

class AJ_DeadMenu : public StateUIBase
{
public:
    AJ_DeadMenu();
    bool onEnter();
    bool onExit();
    void update();
    std::string getStateID();
    static void buttonOK(const CEGUI::EventArgs&);
};

#endif // AJ_DEADMENU_H
