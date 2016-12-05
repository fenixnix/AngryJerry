#include "unitrunner.h"
#include "aj_avatar.h"
#include "objmngr.h"
#include "global.h"
#include "render/nglrender.h"
#include "objmngr.h"

UnitRunner::UnitRunner()
{

}

void UnitRunner::update()
{
    Unit::update();
    Unit* avt = dynamic_cast<Unit*>(ObjMngr::the()->getObj(AJ_Avatar::the()->avatarID));
    if(avt){
        b2Vec2 d = avt->phyxBody->GetTransform().p;
        b2Vec2 s = this->phyxBody->GetTransform().p;
        b2Vec2 dir = d-s;
        dir.Normalize();
        phyxBody->ApplyForce(b2Vec2(dir.x*2,dir.y*2),b2Vec2(0,0),true);
    }else{
        phyxBody->ApplyForce(b2Vec2(-2,0),b2Vec2(0,0),true);
    }
    if(gt.getTo()){
        this->jump();       
        gt.start(1500);
      }
}

void UnitRunner::signalDie()
{
  ObjMngr::the()->createItem("Exp",this->phyxBody->GetTransform().p.x,this->phyxBody->GetTransform().p.y);
  ObjMngr::the()->createItem("Exp",this->phyxBody->GetTransform().p.x,this->phyxBody->GetTransform().p.y);
  if(rand()%100<=50){
      ObjMngr::the()->createItem("Health",this->phyxBody->GetTransform().p.x,this->phyxBody->GetTransform().p.y);
    }
}

void UnitRunner::draw()
{
  Global::the()->unitImageSet.useSet();
  Global::the()->unitImageSet.draw(this->phyxBody->GetTransform().p.x,
                                   this->phyxBody->GetTransform().p.y,
                                   1,1,0,"Enemy1");
}
