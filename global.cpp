#include "global.h"

Global* Global::pStatic = nullptr;

Global::Global()
{
    isDrawDebug = true;
}

Global *Global::the(){
    if(pStatic == nullptr){
        pStatic = new Global;
    }
    return pStatic;
}
