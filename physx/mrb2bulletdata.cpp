#include "mrb2bulletdata.h"

MRb2BulletData::MRb2BulletData()
{
    type = MRb2Data::type_bullet;
    dmg = 0.1;
}

float MRb2BulletData::getDmg()
{
    return dmg;
}
