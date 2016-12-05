#ifndef AJ_PHYSXPREFAB_H
#define AJ_PHYSXPREFAB_H

#include "b2physx.h"
#include "singleton.h"

class AJ_PhysxPrefab : public NSingleton<AJ_PhysxPrefab>
{
public:
    AJ_PhysxPrefab();
    b2Body *createPlayer(b2Vec2 loc,void* data);
    b2Body *createPlayerBullet(b2Vec2 loc, b2Vec2 dir, void* data);
    b2Body *createEnemy(b2Vec2 loc,void* data);
    b2Body *createEnemyBullet(b2Vec2 loc, b2Vec2 dir, void* data);
    b2Fixture *createEnemyWall(b2Vec2 p1, b2Vec2 p2);
    b2Body *createPlayerGrenadiers(b2Vec2 loc, b2Vec2 dir, void* data);
    b2Body *createExplosive(b2Vec2 loc, float r, void* data);
    b2Body *createBoostItem(b2Vec2 loc, float r, void* data);

    void createCamera(b2Vec2 loc);
    void setCameraAim(b2Vec2 aimLoc);
    void getCameraPos(float &x, float &y);
private:
    b2Body* cam;
    b2Filter filterPlayer;
    b2Filter filterPlayerBullet;
    b2Filter filterEnemy;
    b2Filter filterEnemyBullet;
    b2Filter filterExplosive;
    b2Filter filterBoostItem;
};

#endif // AJ_PHYSXPREFAB_H
