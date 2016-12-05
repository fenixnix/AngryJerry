#ifndef AJ_AVATAR_H
#define AJ_AVATAR_H

#include "singleton.h"
#include "unit.h"
#include "levelexp.h"

class AJ_Avatar : public NSingleton<AJ_Avatar>
{
public:
    AJ_Avatar();
    int avatarID;
    void update();
    void render();
    void create(float x, float y);
    void release();
    void force(float x, float y);
    void impact(float x, float y);
    void jump();
    void charge();
    void shoot1(float x, float y);
    void shoot(float x, float y);
    bool canUpgrade();
    void health(int life);
    void costSkillPoint(string skillID);
    void reloadWeapon1();
    float getPower();
    float getAmmoPercent();
    void gainExp(int exp);
    LevelExp lvExp;
    int getSkillPoint() const;

private:
    int ammo;
    int ammoMax;
    int weapon1ReloadTime;
    bool weapon1Reloading;
    bool isCharging;
    float power;
    float power1;
    float chargeSpeed;
    int shootTempo;
    float sightXoffset;
    float sightYoffset;
    int skillPoint;
};

#endif // AJ_AVATAR_H
