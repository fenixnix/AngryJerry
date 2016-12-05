#include <gameapp.h>
#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int iCmdShow){
    GameApp::the()->init("Game",800,600);
    GameApp::the()->run();
    GameApp::the()->release();
    SDL_Quit();
    return 0;
}
