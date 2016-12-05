#include "aj_input.h"
#include "Render/nglrender.h"
#include "global.h"
#include "aj_avatar.h"
#include "objmngr.h"

AJ_Input::AJ_Input()
{
    NGLRender::the()->getWindow(NGLRender::windowGame)->zoomOut();
    NGLRender::the()->getWindow(NGLRender::windowGame)->zoomOut();
    NGLRender::the()->getWindow(NGLRender::windowGame)->zoomOut();
}

void AJ_Input::keyDown(SDL_Scancode code)
{
  switch (code) {
    case SDL_SCANCODE_1:
      ObjMngr::the()->createItem("Health",0,3);
      break;
    case SDL_SCANCODE_2:
      ObjMngr::the()->createItem("Exp",0,3);
      break;
    case SDL_SCANCODE_3:
      ObjMngr::the()->createItem("Sheild",0,3);
      break;
    case SDL_SCANCODE_4:
      ObjMngr::the()->createItem("SpeedUp",0,3);
      break;
    case SDL_SCANCODE_5:
      ObjMngr::the()->createItem("Infinity",0,3);
      break;
    case SDL_SCANCODE_6:
      ObjMngr::the()->createItem("Run",0,3);
      break;
    default:
      break;
    }
}

void AJ_Input::mouseWheelDown()
{
    //SDL_GL_Window * gameWindow = SDL_Render::the()->windows["game"];
    NGLRender::the()->getWindow(NGLRender::windowGame)->zoomOut();
    //gameWindow->zoomOut();
}

void AJ_Input::mouseWheelUp()
{
    //SDL_GL_Window * gameWindow = SDL_Render::the()->windows["game"];
    NGLRender::the()->getWindow(NGLRender::windowGame)->zoomIn();
    //gameWindow->zoomIn();
}
