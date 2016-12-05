#include "unitgrenadiers.h"
#include "bullet.h"
#include "objmngr.h"
#include "global.h"

UnitGrenadiers::UnitGrenadiers()
{

}

void UnitGrenadiers::update()
{
    Unit::update();
    b2Transform tra = phyxBody->GetTransform();
    if(gt.getTo()){
        if(gt.getTo()){
            float rd = rand()%10*0.03;
            Bullet::create("ebullet",tra.p.x,tra.p.y,-0.2,0.3+rd);
            gt.start(3000);
        }
      }
}

void UnitGrenadiers::draw()
{
  Global::the()->unitImageSet.useSet();
  Global::the()->unitImageSet.draw(this->phyxBody->GetTransform().p.x,
                                   this->phyxBody->GetTransform().p.y,
                                   1,1,0,"Enemy2");
}

void UnitGrenadiers::signalDie()
{
    ObjMngr::the()->createItem("Exp",this->phyxBody->GetTransform().p.x,this->phyxBody->GetTransform().p.y);
}
