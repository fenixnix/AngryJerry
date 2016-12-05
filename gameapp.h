#ifndef GAMEAPP_H
#define GAMEAPP_H

#include "SDL.h"
#include "string"
#include "singleton.h"

using namespace std;

class GameApp : public NSingleton<GameApp>
{
public:
    GameApp();
    void init(string title, int w, int h);
    void run();
    void release();
    bool isRuning;
};

#endif // GAMEAPP_H
