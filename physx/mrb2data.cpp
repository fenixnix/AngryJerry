#include "mrb2data.h"

MRb2Data::MRb2Data()
{
    type = type_unknow;
}

void MRb2Data::dealContact(MRb2Data *data)
{
    //cout<<__FUNCTION__<<__LINE__<<endl;
}

MRb2Data::DataType MRb2Data::getType()
{
    return type;
}

MRb2ShapeData *MRb2Data::toMRb2ShapeData()
{
    return (MRb2ShapeData*)this;
}

MRb2BulletData *MRb2Data::toMRb2BulletData()
{
    return (MRb2BulletData*)this;
}
