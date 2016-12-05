#ifndef UNITGRENADIERS_H
#define UNITGRENADIERS_H

#include "unit.h"

class UnitGrenadiers : public Unit
{
public:
    UnitGrenadiers();
    void update();
    void draw();
    void signalDie();
};

#endif // UNITGRENADIERS_H
