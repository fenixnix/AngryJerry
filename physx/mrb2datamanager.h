#ifndef MRB2DATAMANAGER_H
#define MRB2DATAMANAGER_H

#include "b2unit.h"
#include "mrb2shapedata.h"
#include "mrb2bulletdata.h"
#include "singleton.h"
/**
 * @brief The MRb2DataManager class
 */
enum UpdateState{state_unknow = 0,state_normal,state_dead};

class MRb2DataManager : public NSingleton<MRb2DataManager>
{
public:
    MRb2DataManager();
    void update();//update shape destroy
    UpdateState update(B2Unit* unit);//return true mean dead
    UpdateState update(B2UnitBody* unitBody);//return true mean dead
    UpdateState update(b2Fixture* fixture);//return true mean dead
    B2Unit *createUnit(std::string id,b2Transform tra = b2Transform(b2Vec2(0,0),b2Rot(0)));
    void destoryUnit(B2Unit* unit);
    static void initB2UnitShapeData(B2Unit* unit);

    static void initShapeData(b2Fixture* fixture);
    static void initBulletData(b2Fixture* fixture);

    static void delFixture(b2Fixture* fixture);
private:
    std::vector<B2Unit*> units;
};

#endif // MRB2DATAMANAGER_H
