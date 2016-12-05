#ifndef MRB2DATAMANAGER_H
#define MRB2DATAMANAGER_H

#include "b2unit.h"
#include "mrb2shapedata.h"
#include "mrb2bulletdata.h"
#include "singleton.h"

class MRb2DataManager : public NSingleton<MRb2DataManager>
{
public:
    MRb2DataManager();
    static void initB2UnitShapeData(B2Unit* unit);

    static void initShapeData(b2Fixture* fixture);
    static void initBulletData(b2Fixture* fixture);
};

#endif // MRB2DATAMANAGER_H
