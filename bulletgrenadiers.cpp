#include "bulletgrenadiers.h"
#include "unit.h"
#include "nfmodmngr.h"

BulletGrenadiers::BulletGrenadiers()
{

}

void BulletGrenadiers::begin(PhysxObj *po)
{
    //cout<<__FUNCTION__<<endl;
    if(po != nullptr){
        if(po->isUnit()){
            cout<<__FUNCTION__<<"process dmg!!!"<<endl;
            Unit *dUnit = dynamic_cast<Unit*>(po);
            dUnit->takeDmg(1);
            b2Vec2 s = this->phyxBody->GetTransform().p;
            b2Vec2 d = po->phyxBody->GetTransform().p;
            b2Vec2 dft = d - s;
            dft.x*=3;
            dft.y*=3;
            //po->phyxBody->ApplyLinearImpulse(dft,b2Vec2(0,0),true);
            NFMODMngr::the()->trigOneShot("Explosions:Single Explosion",s.x,s.y,0);
            Bullet::create("explosive",s.x,s.y,0,0);
            this->isDead = true;
        }
    }
    //isDead = true;
}

