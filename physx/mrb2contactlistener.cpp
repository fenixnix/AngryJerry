#include "mrb2contactlistener.h"
#include "mrb2data.h"

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
}
