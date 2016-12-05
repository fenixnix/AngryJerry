#include "aj_avatar.h"
#include "aj_physxprefab.h"
#include "Render/nglrender.h"
#include "aj_map.h"
#include "unit.h"
#include "bullet.h"
#include "globaltimer.h"
#include "nfmodmngr.h"
#include "physx/mrb2datamanager.h"

GlobalTimer shootTimer;
GlobalTimer weapon1ReloadTimer;

Unit* avt;
b2Body* avatarBody = nullptr;
b2Transform avatarTra;
b2Vec2 shootDir;

AJ_Avatar::AJ_Avatar()
{
  power = 0.0;
  power1 = 1.0;
  chargeSpeed = 0.03;
  isCharging = false;
  weapon1Reloading = false;
  shootTempo = 50;
  sightXoffset = 4;
  sightYoffset = 0;
  ammo = 30;
  ammoMax = 30;
  weapon1ReloadTime = 1000;
  skillPoint = 0;
  avt = nullptr;
  shootTimer.start(shootTempo);
}

void AJ_Avatar::update()
{
  if(avatarBody){
      avatarTra = avatarBody->GetTransform();
      float mx,my,mz;
      NGLRender::the()->getMousePos(mx,my,mz);
      b2Vec2 dir(mx,my);
      dir = dir - avatarTra.p;
      dir.Normalize();
      shootDir.x = dir.x;
      shootDir.y = dir.y;

      if(dir.x>0){
          sightXoffset = 3;
        }else{
          sightXoffset = -3;
        }

      AJ_PhysxPrefab::the()->setCameraAim(b2Vec2(avatarTra.p.x + sightXoffset,avatarTra.p.y + sightYoffset));
      float cx,cy;
      AJ_PhysxPrefab::the()->getCameraPos(cx,cy);

      NGLWindow *win = NGLRender::the()->getWindow(NGLRender::windowGame);
      //        win->cam_x = avatarTra.p.x + sightXoffset;
      //        win->cam_y = avatarTra.p.y + sightYoffset;

      win->cam_x = cx;
      win->cam_y = cy;


      AJ_Map::the()->updatePos(avatarTra.p.x);
      //NFMODMngr::the()->getEvent("music")->setParameterValue("Level",x);
      NFMODMngr::the()->setListenerPos(avatarTra.p.x,avatarTra.p.y,10);
    }
}

void AJ_Avatar::render()
{
  if(avatarBody){
      NGLRender* render = NGLRender::the();
      render->setMode(MODE_GEO);
      render->drawLine(avatarTra.p.x,avatarTra.p.y,0,avatarTra.p.x+shootDir.x,avatarTra.p.y+shootDir.y,0,
                       0,1,0,1,1,0,0,0);


      if(isCharging){

          //NGLWindow * w = render->getWindow(NGLRender::windowGame);
          float cl[] = {1,1,0,0.5};
          float cl1[] = {0,1,0,0.3};
          render->drawCircle(avatarTra.p.x,avatarTra.p.y,-0.1,1,cl,GL_LINE_LOOP);
          render->drawCircle(avatarTra.p.x,avatarTra.p.y,-0.1,power,cl1,GL_POLYGON);
        }
    }
}

void AJ_Avatar::create(float x, float y)
{
  //avatarBody = AJ_PhysxPrefab::the()->createAvatar(0,0);
  avt = Unit::create("avatar",x,y);
  avatarID = avt->id;
  avatarBody = avt->phyxBody;
  AJ_PhysxPrefab::the()->createCamera(avt->phyxBody->GetTransform().p);
}

void AJ_Avatar::release()
{
  if(avatarBody){
      B2Physx::the()->world->DestroyBody(avatarBody);
    }
}

void AJ_Avatar::force(float x, float y)
{
  avatarBody->ApplyForce(b2Vec2(x,y),b2Vec2(0,0),true);

}

void AJ_Avatar::impact(float x, float y)
{
  avatarBody->ApplyLinearImpulse(b2Vec2(x,y),b2Vec2(0,0),true);
}

void AJ_Avatar::jump()
{
  avt->jump();
}

void AJ_Avatar::charge()
{
  isCharging = true;
  if(power<=1){
      power+=chargeSpeed;
    }
}

void AJ_Avatar::shoot1(float x, float y)
{
  if(ammo>0){
      if(shootTimer.getTo()){
          NFMODMngr::the()->trigOneShot("Weapons:Single-Shot",avatarTra.p.x,avatarTra.p.y,0);
          float ry = (float)(rand()%100)/500.0f;
          Bullet* bullet = Bullet::create("bullet",avatarTra.p.x,avatarTra.p.y,shootDir.x*power1,shootDir.y*power1+ry);
          ///
            MRb2DataManager::the()->initBulletData(bullet->phyxBody->GetFixtureList());
          ///
          ammo--;
          shootTimer.start(shootTempo);
        }
    }else{
      reloadWeapon1();
    }
}

void AJ_Avatar::shoot(float x, float y)
{

  isCharging = false;
  if(power<=0.4){
      power = 0.4;
    }
  Bullet::create("grenadiers",avatarTra.p.x,avatarTra.p.y,shootDir.x*power*30,shootDir.y*power*30);
  power = 0;
}

bool AJ_Avatar::canUpgrade()
{
  if(skillPoint>0){
      return true;
    }
  return false;
}

void AJ_Avatar::health(int life)
{
  avt->health(life);
}

void AJ_Avatar::costSkillPoint(string skillID)
{
  if(skillPoint<=0)
    return;

  if(skillID == "Ammo"){
      ammoMax*=1.2;
    }
  if(skillID == "RapidFire"){
      shootTempo*=0.9;
    }
  if(skillID == "RapidReload"){
      weapon1ReloadTime*=0.9;
    }

  skillPoint --;
}

void AJ_Avatar::reloadWeapon1()
{
  if(!weapon1Reloading){
      weapon1ReloadTimer.start(weapon1ReloadTime);
      weapon1Reloading = true;
    }
  if(weapon1Reloading = true){
      if(weapon1ReloadTimer.getTo()){
          ammo = ammoMax;
          weapon1Reloading = false;
        }
    }
}

float AJ_Avatar::getPower()
{
  return power;
}

float AJ_Avatar::getAmmoPercent()
{
  return (float)(((float)ammo)/((float)ammoMax));
}

void AJ_Avatar::gainExp(int exp)
{
  skillPoint+=lvExp.addExp(exp);
}

int AJ_Avatar::getSkillPoint() const
{
  return skillPoint;
}
