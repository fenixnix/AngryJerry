#ifndef AJ_ENDLESSGAME_H
#define AJ_ENDLESSGAME_H

#include "FSM/finitystate.h"

class AJ_EndlessGame : public FinityState
{
public:
    AJ_EndlessGame();
    bool onEnter();
    bool onExit();
    void update();
    void render();
};

#endif // AJ_ENDLESSGAME_H
