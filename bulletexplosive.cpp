#include "bulletexplosive.h"
#include "unit.h"
#include "global.h"

BulletExplosive::BulletExplosive()
{

}

void BulletExplosive::begin(PhysxObj *po)
{
    if(po != nullptr){
        if(po->isUnit()){
            cout<<__FUNCTION__<<"process dmg!!!"<<endl;
            Unit *dUnit = dynamic_cast<Unit*>(po);
            dUnit->takeDmg(3);
            b2Vec2 s = this->phyxBody->GetTransform().p;
            b2Vec2 d = po->phyxBody->GetTransform().p;
            b2Vec2 dft = d - s;
            dft.x*=3;
            dft.y*=3;
            po->phyxBody->ApplyLinearImpulse(dft,b2Vec2(0,0),true);
        }
      }
}

void BulletExplosive::draw()
{
  cout<<__FUNCTION__<<endl;
  Global::the()->unitImageSet.useSet();
  Global::the()->unitImageSet.draw(this->phyxBody->GetTransform().p.x,
                                   this->phyxBody->GetTransform().p.y,
                                   3,3,0,"Explosive");
}
