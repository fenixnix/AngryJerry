#ifndef AJ_GAMEUI_H
#define AJ_GAMEUI_H

#include "FSM/finitystate.h"

class AJ_GameUI : public FinityState
{
public:
    AJ_GameUI();
    bool onEnter();
    bool onExit();
    void update();
    void render();
    bool injectKeyDown(int keyCode);
    bool injectKeyUp(int keyCode);
    bool injectMouseRightDown();
    bool injectMouseRightUp();
    bool injectMouseLeftDown();
    bool injectMouseLeftUp();
private:
    bool lk;
    bool rk;
    bool mouseRb;
    bool mouseLb;
    float mx,my,mz;
};

#endif // AJ_GAMEUI_H
