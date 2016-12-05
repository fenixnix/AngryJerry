#ifndef MRB2BULLETDATA_H
#define MRB2BULLETDATA_H

#include "mrb2data.h"

class MRb2BulletData : public MRb2Data
{
public:
    MRb2BulletData();
    float getDmg();
private:
    float dmg;
};

#endif // MRB2BULLETDATA_H
