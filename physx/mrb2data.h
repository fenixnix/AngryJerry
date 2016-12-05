#ifndef MRB2DATA_H
#define MRB2DATA_H

#include <iostream>

using namespace std;

class MRb2ShapeData;
class MRb2BulletData;

class MRb2Data
{
public:
    MRb2Data();
    enum DataType{type_unknow = 0, type_shape, type_bullet};
    virtual void dealContact(MRb2Data* data);
    virtual DataType getType();

    MRb2ShapeData *toMRb2ShapeData();
    MRb2BulletData *toMRb2BulletData();
protected:
    DataType type;
};

#endif // MRB2DATA_H
