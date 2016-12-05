#include "gameapp.h"
#include "Render/nglrender.h"
#include "FSM/fsm.h"
#include "global.h"
#include "globaltimer.h"
#include "FSM/aj_mainui.h"
#include "b2physx.h"
#include "aj_map.h"
#include "Render/nglimageset.h"
#include "time.h"
#include "nfmodmngr.h"
#include "b2objunitmanager.h"
#include "physx/mrb2contactlistener.h"

GlobalTimer fpsTimer;
int fpsCnt;

GameApp::GameApp()
{
    ///time random seed gen
    srand(time(NULL));
    fpsTimer.start(1000);
    fpsCnt = 0;
}

void GameApp::init(string title, int w, int h)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) >= 0)
    {
        NGLRender::the()->init(title, w, h);
        NFMODMngr::the()->init();
        B2Physx::the()->init(0,-9.8);
        B2Physx::the()->setListener(MRb2ContactListener::the());
        B2Physx::the()->setDraw(&Global::the()->physxDraw);
        AJ_Map::the()->init(rand());
        NGUI::the()->init();
        Global::the()->iconImageSet.loadImageSet("AJ_Icon.imageset");
        Global::the()->unitImageSet.loadImageSet("Unit001.imageset");

        Global::the()->techTree.loadTree("AJ_Tech.xml");
        Global::the()->techTree.getAllTech();

        B2ObjUnitManager::the()->setb2World(B2Physx::the()->world);
        B2ObjUnitManager::the()->init();

        FSM::the()->pushState(new AJ_MainUI);
        isRuning = true;
        return;
    }
    B2Physx::the()->release();
    cout<<"sdl could not initialize!!!"<<endl;
}

void GameApp::run()
{
    while(isRuning){
        GlobalTimer::update();

        if(fpsTimer.getTo()){
            Global::the()->fps = fpsCnt;
            fpsCnt = 0;
            fpsTimer.start(1000);
          }
        fpsCnt++;

        FSM::the()->update();
        FSM::the()->render();
    }
    FSM::the()->popState();
}

void GameApp::release()
{
    delete this;
}
