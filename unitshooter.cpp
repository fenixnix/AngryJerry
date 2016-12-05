#include "unitshooter.h"
#include "bullet.h"
#include "objmngr.h"
#include "global.h"

UnitShooter::UnitShooter()
{

}

void UnitShooter::update()
{
    Unit::update();
    b2Transform tra = phyxBody->GetTransform();
    if(gt.getTo()){
        float rd = rand()%10*-0.1;
        Bullet::create("ebullet",tra.p.x,tra.p.y,-0.5+rd,0);
        gt.start(3000*100/(tra.p.x));
      }
}

void UnitShooter::draw()
{
  Global::the()->unitImageSet.useSet();
  Global::the()->unitImageSet.draw(this->phyxBody->GetTransform().p.x,
                                   this->phyxBody->GetTransform().p.y,
                                   1,1,0,"Enemy0");
}

void UnitShooter::signalDie()
{
  ObjMngr::the()->createItem("Exp",this->phyxBody->GetTransform().p.x,this->phyxBody->GetTransform().p.y);
}
