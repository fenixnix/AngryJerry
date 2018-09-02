#include "aj_endlessgame.h"
#include "time.h"
#include "aj_map.h"
#include "objmngr.h"
#include "aj_avatar.h"
#include "Render/nglrender.h"
#include "global.h"

NGLRender * nglRender = nullptr;
NGLWindow * renderWindow = nullptr;

AJ_EndlessGame::AJ_EndlessGame()
{

}

bool AJ_EndlessGame::onEnter()
{
    //cout<<__FUNCTION__<<__LINE__<<endl;
    B2Physx::the()->createWorldBaseObj();
    AJ_Map::the()->generate(0);
    //cout<<__FUNCTION__<<__LINE__<<endl;
    AJ_Avatar::the()->create(0,2);
    //cout<<__FUNCTION__<<__LINE__<<endl;

    return true;
}

bool AJ_EndlessGame::onExit()
{
    //cout<<__FUNCTION__<<__LINE__<<endl;
    //AJ_Avatar::the()->release();
    //cout<<__FUNCTION__<<__LINE__<<endl;
    //ObjMngr::the()->destoryAll();
    ObjMngr::the()->release();
    //cout<<__FUNCTION__<<__LINE__<<endl;
    AJ_Map::the()->release();
   // cout<<__FUNCTION__<<__LINE__<<endl;
    //B2Physx::the()->printDebug();
    B2Physx::the()->clearBody();
    //B2Physx::the()->printDebug();
    return true;
}

#include "physx/mrb2datamanager.h"
#include "b2fragmentfactory.h"
void AJ_EndlessGame::update()
{
    ObjMngr::the()->update();
    B2Physx::the()->update();
    MRb2DataManager::the()->update();
    B2FragmentFactory::the()->update();
}

void AJ_EndlessGame::render()
{
    nglRender = NGLRender::the();
    renderWindow = nglRender->getWindow(NGLRender::windowGame);
    renderWindow->setOrtho();
    //renderWindow->setCamera(0,0);
    nglRender->setVP(renderWindow);
    AJ_Map::the()->render();
    AJ_Avatar::the()->render();
    glDisable(GL_DEPTH_TEST);


    if(Global::the()->isDrawDebug){
        NGLRender* render = NGLRender::the();
        render->setMode(MODE_GEO);
        B2Physx::the()->render();
    }

    ObjMngr::the()->render();

}
