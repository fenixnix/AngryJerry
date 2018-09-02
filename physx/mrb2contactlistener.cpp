#include "mrb2contactlistener.h"
#include "mrb2data.h"
#include "physxobj.h"

MRb2ContactListener::MRb2ContactListener()
{

}

void MRb2ContactListener::BeginContact(b2Contact *contact)
{
    MRb2Data* dataA = (MRb2Data*)contact->GetFixtureA()->GetUserData();
    MRb2Data* dataB = (MRb2Data*)contact->GetFixtureB()->GetUserData();
    if(dataA!=nullptr){
        dataA->dealContact(dataB);
    }
    if(dataB!=nullptr){
        dataB->dealContact(dataA);
    }

    PhysxObj* A = static_cast<PhysxObj*>(contact->GetFixtureA()->GetBody()->GetUserData());
    PhysxObj* B = static_cast<PhysxObj*>(contact->GetFixtureB()->GetBody()->GetUserData());

    if(A!=nullptr){
        A->addConnect(B);
    }
    if(B!=nullptr){
        B->addConnect(A);
    }
}

void MRb2ContactListener::EndContact(b2Contact *contact)
{
    PhysxObj* A = static_cast<PhysxObj*>(contact->GetFixtureA()->GetBody()->GetUserData());
    PhysxObj* B = static_cast<PhysxObj*>(contact->GetFixtureB()->GetBody()->GetUserData());
    if((A!=NULL)&&(B!=NULL)){
        A->disConnect(B);
        B->disConnect(A);
    }
}
