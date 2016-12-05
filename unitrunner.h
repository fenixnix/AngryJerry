#ifndef UNITRUNNER_H
#define UNITRUNNER_H

#include "unit.h"

class UnitRunner : public Unit
{
public:
    UnitRunner();
    void update();
    void signalDie();
    void draw();
};

#endif // UNITRUNNER_H
