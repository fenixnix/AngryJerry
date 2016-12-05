#ifndef BULLETGRENADIERS_H
#define BULLETGRENADIERS_H

#include "bullet.h"

class BulletGrenadiers : public Bullet
{
public:
    BulletGrenadiers();
    void begin(PhysxObj *po);
};

#endif // BULLETGRENADIERS_H
