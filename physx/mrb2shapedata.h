#ifndef MRB2SHAPEDATA_H
#define MRB2SHAPEDATA_H

#include "mrb2data.h"

class MRb2ShapeData : public MRb2Data
{
public:
    MRb2ShapeData();
    void dealContact(MRb2Data* data);
    void setMass(float mass);
    float getMass();

private:
    float mass;
};

#endif // MRB2SHAPEDATA_H
