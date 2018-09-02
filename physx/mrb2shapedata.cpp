#include "mrb2shapedata.h"
#include "mrb2bulletdata.h"

#include "mrb2datamanager.h"

MRb2ShapeData::MRb2ShapeData()
{
    mass = 0.0f;
    type = MRb2Data::type_shape;
}

void MRb2ShapeData::dealContact(MRb2Data *data)
{
    if(data == nullptr){
        return;
    }
    if(data->getType() == MRb2Data::type_bullet){
        mass -= data->toMRb2BulletData()->getDmg();
//        if(mass<=0){
//            MRb2DataManager::delFixture()
//            cout<<__FUNCTION__<<__LINE__<<"break this shape"<<endl;
//        }
    }
}

void MRb2ShapeData::setMass(float mass)
{
    this->mass = mass;
}

float MRb2ShapeData::getMass()
{
    return mass;
}
