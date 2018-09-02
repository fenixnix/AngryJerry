#include "mrb2datamanager.h"
#include "b2objunitmanager.h"
#include "b2polygon.h"
#include "b2fragmentfactory.h"

MRb2DataManager::MRb2DataManager()
{
    units.clear();
}

void MRb2DataManager::update()
{
    //cout<<__FUNCTION__<<endl;
    for(auto itr = units.begin();itr!=units.end();itr++){
        B2Unit *unit = (*itr);
        if(update(unit) == state_dead){
            destoryUnit(unit);//!!!!
        }
    }
}

UpdateState MRb2DataManager::update(B2Unit *unit)
{
    list<string> bodyIDList = unit->getBodyList();
    for(auto itr = bodyIDList.begin();itr!=bodyIDList.end();itr++){
        string bodyID = (*itr);
        B2UnitBody* unitBody = unit->getB2UnitBody(bodyID);
        UpdateState state = update(unitBody);
        if(state == state_dead){
            if(bodyID == "body"){
                cout<<__FUNCTION__<<":"<<__LINE__<<" body destroy!!!"<<endl;
                return state_dead;
            }
        }
    }
    return state_normal;
}

/**
 * @brief MRb2DataManager::update
 * @param unitBody
 */
UpdateState MRb2DataManager::update(B2UnitBody *unitBody)
{
    list<string> fixtureIDList = unitBody->getFixtureList();

    if(fixtureIDList.empty()){
        return state_dead;
    }

    for(auto itr = fixtureIDList.begin();itr!=fixtureIDList.end();itr++){
        string fixtureID = (*itr);
        b2Fixture* fixture = unitBody->getFixture(fixtureID);
        if(update(fixture) == state_dead){
            //fixture dead
            B2FragmentFactory::the()->createFragment(fixture);
            this->delFixture(fixture);//使用了不同的迭代器（字符串索引）所以删除不会出错
            unitBody->delFixture(fixtureID);
        }
    }
    return state_normal;
}

UpdateState MRb2DataManager::update(b2Fixture *fixture)
{
    MRb2Data* data = (MRb2Data*)fixture->GetUserData();
    MRb2Data::DataType dataType = data->getType();
    if(dataType == MRb2Data::type_shape){
        MRb2ShapeData* shapeData = data->toMRb2ShapeData();
        if(shapeData->getMass()<=0){
            return state_dead;
        }
    }
    if(dataType == MRb2Data::type_bullet){

    }
    return state_normal;
}

B2Unit *MRb2DataManager::createUnit(string id, b2Transform tra)
{
    B2Unit *unit = B2ObjUnitManager::the()->createB2Unit(id,tra);
    units.push_back(unit);
    return unit;
}

void MRb2DataManager::destoryUnit(B2Unit *unit)
{
    //小心迭代器内删除！！！
}

void MRb2DataManager::initB2UnitShapeData(B2Unit *unit)
{
    list<string> bodyList = unit->getBodyList();
    for(auto itr = bodyList.begin();itr!=bodyList.end();itr++){
        B2UnitBody* unitBody = unit->getB2UnitBody(*itr);
        list<string> fixtureList = unitBody->getFixtureList();
        for(auto fixtureItr = fixtureList.begin();fixtureItr!=fixtureList.end();fixtureItr++){
            b2Fixture* fixture = unitBody->getFixture(*fixtureItr);
            initShapeData(fixture);
        }
    }
}

void MRb2DataManager::initShapeData(b2Fixture *fixture)
{
    b2MassData massData;
    fixture->GetMassData(&massData);
    float mass = massData.mass;
    //cout<<__FUNCTION__<<":mass:"<<mass<<endl;
    MRb2ShapeData* data = new MRb2ShapeData;
    data->setMass(mass);
    fixture->SetUserData(data);
}

void MRb2DataManager::initBulletData(b2Fixture *fixture)
{
    MRb2BulletData* data = new MRb2BulletData;
    fixture->SetUserData(data);
}

void MRb2DataManager::delFixture(b2Fixture *fixture)
{
    delete fixture->GetUserData();
    b2Body* parent = fixture->GetBody();
    parent->DestroyFixture(fixture);
}
