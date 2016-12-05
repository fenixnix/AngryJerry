#ifndef AJ_INPUT_H
#define AJ_INPUT_H

#include "sdl_input.h"
#include "singleton.h"

class AJ_Input : public SDL_Input , public NSingleton<AJ_Input>
{
public:
    AJ_Input();
    void keyDown(SDL_Scancode code);
    void mouseWheelUp();
    void mouseWheelDown();
private:
};

#endif // AJ_INPUT_H
