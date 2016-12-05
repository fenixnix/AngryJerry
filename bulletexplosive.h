#ifndef BULLETEXPLOSIVE_H
#define BULLETEXPLOSIVE_H

#include "bullet.h"

class BulletExplosive : public Bullet
{
public:
    BulletExplosive();
    void begin(PhysxObj *po);
    void draw();
};

#endif // BULLETEXPLOSIVE_H
