TEMPLATE = app
#CONFIG += console
CONFIG += c++11
CONFIG -= app_bundle
CONFIG += qt core

SOURCES += main.cpp \
    gameapp.cpp \
    global.cpp \
    ../_src/globaltimer.cpp \
    ../_src/FSM/finitystate.cpp \
    ../_src/FSM/fsm.cpp \
    FSM/aj_mainui.cpp \
    ../_src/FSM/stateuibase.cpp \
    ../_src/sdl_input.cpp \
    aj_input.cpp \
    ../_src/Render/physxdraw.cpp \
    ../_src/obj.cpp \
    aj_avatar.cpp \
    aj_physxprefab.cpp \
    aj_map.cpp \
    FSM/aj_gamemenu.cpp \
    ../_src/unit.cpp \
    ../_src/objmngr.cpp \
    ../_src/structure.cpp \
    ../_src/bullet.cpp \
    FSM/aj_deadmenu.cpp \
    ../_src/unitagent.cpp \
    ../_src/unitaction.cpp \
    ../_src/unitstate.cpp \
    ../_src/unitstateanytime.cpp \
    ../_src/unitdecision.cpp \
    FSM/aj_endlessgame.cpp \
    FSM/aj_gameui.cpp \
    unitshooter.cpp \
    unitgrenadiers.cpp \
    unitrunner.cpp \
    bulletgrenadiers.cpp \
    bulletexplosive.cpp \
    levelexp.cpp \
    ../_src/item.cpp \
    ../_src/ntechtree.cpp \
    ../_src/ntechtreenode.cpp \
    ../_src/nattribute.cpp \
    aj_techtree.cpp \
    FSM/aj_upgrademenu.cpp \
    ../_src/nfmodmngr.cpp \
    physx/mrb2contactlistener.cpp \
    physx/mrb2shapedata.cpp \
    physx/mrb2data.cpp \
    physx/mrb2bulletdata.cpp \
    physx/mrb2datamanager.cpp

HEADERS += \
    gameapp.h \
    global.h \
    ../_src/globaltimer.h \
    ../_src/FSM/finitystate.h \
    ../_src/FSM/fsm.h \
    FSM/aj_mainui.h \
    ../_src/FSM/stateuibase.h \
    ../_src/sdl_input.h \
    aj_input.h \
    ../_src/Render/physxdraw.h \
    ../_src/obj.h \
    ../_src/physxobj.h \
    aj_avatar.h \
    aj_physxprefab.h \
    aj_map.h \
    FSM/aj_gamemenu.h \
    ../_src/unit.h \
    ../_src/objmngr.h \
    ../_src/structure.h \
    ../_src/bullet.h \
    ../_src/singleton.h \
    FSM/aj_deadmenu.h \
    ../_src/unitagent.h \
    ../_src/unitaction.h \
    ../_src/unitstate.h \
    ../_src/unitstateanytime.h \
    ../_src/unitdecision.h \
    FSM/aj_endlessgame.h \
    FSM/aj_gameui.h \
    unitshooter.h \
    unitgrenadiers.h \
    unitrunner.h \
    bulletgrenadiers.h \
    bulletexplosive.h \
    levelexp.h \
    ../_src/item.h \
    ../_src/ntechtree.h \
    ../_src/ntechtreenode.h \
    ../_src/nattribute.h \
    aj_techtree.h \
    FSM/aj_upgrademenu.h \
    ../_src/nfmodmngr.h \
    physx/mrb2contactlistener.h \
    physx/mrb2shapedata.h \
    physx/mrb2data.h \
    physx/mrb2bulletdata.h \
    physx/mrb2datamanager.h

include(D:/workspace/include/SDL2.pri)
include(D:/workspace/include/Box2D.pri)
include(D:/workspace/include/opengl.pri)
include(D:/workspace/include/libnoise.pri)
include(D:/workspace/include/fmod.pri)
include(../_src/render.pri)
include(../_src/ngui.pri)
