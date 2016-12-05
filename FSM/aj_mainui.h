#ifndef AJ_MAINUI_H
#define AJ_MAINUI_H

#include "FSM/stateuibase.h"

class AJ_MainUI : public StateUIBase
{
public:
    AJ_MainUI();
    bool onEnter();
    bool onExit();
    void update();
    std::string getStateID();
    bool injectKeyDown(int keyCode);
    bool injectKeyUp(int keyCode);
    static void buttonStory(const CEGUI::EventArgs&);
    static void buttonEndless(const CEGUI::EventArgs&);
    static void buttonQuit(const CEGUI::EventArgs&);
};

#endif // AJ_MAINUI_H
