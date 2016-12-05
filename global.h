#ifndef GLOBAL_H
#define GLOBAL_H

#include "Render/nglimageset.h"
#include "Render/physxdraw.h"
#include "aj_techtree.h"

class Global
{
public:
    Global();
    static Global *the();
    bool isDrawDebug;
    NGLImageSet iconImageSet;
    NGLImageSet unitImageSet;
    AJ_TechTree techTree;
    int fps;
    PhysxDraw physxDraw;
private:
    static Global * pStatic;
};

#endif // GLOBAL_H
