#include "mrb2datamanager.h"

MRb2DataManager::MRb2DataManager()
{

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
