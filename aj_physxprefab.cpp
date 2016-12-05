#include "aj_physxprefab.h"

AJ_PhysxPrefab* AJ_PhysxPrefab::pStatic = nullptr;

AJ_PhysxPrefab::AJ_PhysxPrefab()
{
    filterPlayer.categoryBits = 0x0002;
    filterPlayer.maskBits = 0x001a;
    filterPlayer.groupIndex = -8;

    filterPlayerBullet.categoryBits = 0x000a;
    filterPlayerBullet.maskBits = 0x000a;
    filterPlayerBullet.groupIndex = -8;

    filterEnemy.categoryBits = 0x000a;
    filterEnemy.maskBits = 0x000b;
    filterEnemy.groupIndex = -4;

    filterEnemyBullet.categoryBits = 0x0010;
    filterEnemyBullet.maskBits = 0x0003;
    filterEnemyBullet.groupIndex = -4;

    filterExplosive.categoryBits = 0x00ff;
    filterExplosive.maskBits = 0x00ff;

    filterBoostItem.categoryBits = 0x0010;
    filterBoostItem.maskBits = 0x0002;

    cam = nullptr;
}

b2Body *AJ_PhysxPrefab::createPlayer(b2Vec2 loc, void *data)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = loc;
    bodyDef.linearDamping = 1.0f;
    bodyDef.angularDamping = 0.2f;
    bodyDef.userData = data;
    b2Body* body = B2Physx::the()->world->CreateBody(&bodyDef);
    b2CircleShape dynamicCircle;
    dynamicCircle.m_p.Set(0,0);
    dynamicCircle.m_radius = 0.3;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicCircle;
    fixtureDef.density = 1.5f;
    fixtureDef.friction = 0.3f;
    fixtureDef.filter = filterPlayer;
    body->CreateFixture(&fixtureDef);
    return body;
}

b2Body *AJ_PhysxPrefab::createPlayerBullet(b2Vec2 loc, b2Vec2 dir, void *data)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = loc;
    bodyDef.linearDamping = 0.5f;
    bodyDef.fixedRotation = true;
    bodyDef.angularDamping = 0.0f;
    bodyDef.userData = data;
    bodyDef.bullet = true;
    b2Body* body = B2Physx::the()->world->CreateBody(&bodyDef);
    b2CircleShape dynamicCircle;
    dynamicCircle.m_p.Set(0,0);
    dynamicCircle.m_radius = 0.05;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicCircle;
    fixtureDef.density = 10.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.filter.categoryBits = 0x000a;
    fixtureDef.filter.maskBits = 0x000a;
    fixtureDef.filter.groupIndex = -8;

    b2Body* t_body = body;

    body->CreateFixture(&fixtureDef);

    if(body!=0){
        //buildBody.push_back(t_body);
    }
    body->ApplyLinearImpulse(dir,b2Vec2(0,0),true);
    return body;
}

b2Body *AJ_PhysxPrefab::createEnemy(b2Vec2 loc, void *data)
{
    //cout<<__FUNCTION__<<__LINE__<<endl;
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.linearDamping = 1.0f;
    bodyDef.angularDamping = 0.2f;
    bodyDef.position = loc;
    bodyDef.userData = data;
    b2Body* body = nullptr;
    while(body == nullptr){
        body = B2Physx::the()->world->CreateBody(&bodyDef);
    }
    //cout<<__FUNCTION__<<__LINE__<<body<<endl;
    b2CircleShape dynamicCircle;
    dynamicCircle.m_p.Set(0,0);
    dynamicCircle.m_radius = 0.3;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicCircle;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.filter.categoryBits = 0x000a;
    fixtureDef.filter.maskBits = 0x000b;
    fixtureDef.filter.groupIndex = -4;
    //cout<<__FUNCTION__<<__LINE__<<endl;
    b2Fixture* fix = nullptr;
    while(fix == nullptr){
        fix = body->CreateFixture(&fixtureDef);
    }
    //cout<<__FUNCTION__<<__LINE__<<endl;
    return body;
}

b2Body *AJ_PhysxPrefab::createEnemyBullet(b2Vec2 loc, b2Vec2 dir, void *data)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = loc;
    bodyDef.linearDamping = 1.0f;
    bodyDef.fixedRotation = true;
    bodyDef.angularDamping = 0.0f;
    bodyDef.userData = data;
    bodyDef.bullet = true;
    b2Body* body = B2Physx::the()->world->CreateBody(&bodyDef);
    b2CircleShape dynamicCircle;
    dynamicCircle.m_p.Set(0,0);
    dynamicCircle.m_radius = 0.1;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicCircle;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.filter.categoryBits = 0x0010;
    fixtureDef.filter.maskBits = 0x0003;
    fixtureDef.filter.groupIndex = -4;

    b2Body* t_body = body;

    body->CreateFixture(&fixtureDef);

    if(body!=0){
        //buildBody.push_back(t_body);
    }
    body->ApplyLinearImpulse(dir,b2Vec2(0,0),true);
    return body;
}

b2Fixture *AJ_PhysxPrefab::createEnemyWall(b2Vec2 p1, b2Vec2 p2)
{
    b2EdgeShape esp;
    esp.Set(p1,p2);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &esp;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.filter.categoryBits = 0x0008;
    fixtureDef.filter.maskBits = 0x0008;
    return B2Physx::the()->worldBase->CreateFixture(&fixtureDef);
}

b2Body *AJ_PhysxPrefab::createPlayerGrenadiers(b2Vec2 loc, b2Vec2 dir, void *data)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = loc;
    bodyDef.linearDamping = 0.5f;
    bodyDef.fixedRotation = true;
    bodyDef.angularDamping = 0.0f;
    bodyDef.userData = data;
    bodyDef.bullet = true;
    b2Body* body = B2Physx::the()->world->CreateBody(&bodyDef);
    b2CircleShape dynamicCircle;
    dynamicCircle.m_p.Set(0,0);
    dynamicCircle.m_radius = 0.2;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicCircle;
    fixtureDef.density = 10.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.filter = filterPlayerBullet;
    b2Body* t_body = body;
    body->CreateFixture(&fixtureDef);

    if(body!=0){
        //buildBody.push_back(t_body);
    }
    body->ApplyLinearImpulse(dir,b2Vec2(0,0),true);
    return body;
}

b2Body *AJ_PhysxPrefab::createExplosive(b2Vec2 loc, float r, void *data)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position = loc;
    bodyDef.userData = data;
    bodyDef.bullet = true;

    b2Body* body = B2Physx::the()->world->CreateBody(&bodyDef);
    b2CircleShape dynamicCircle;
    dynamicCircle.m_p.Set(0,0);
    dynamicCircle.m_radius = r;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicCircle;
    fixtureDef.filter = filterExplosive;
    b2Body* t_body = body;
    body->CreateFixture(&fixtureDef);

    if(body!=0){
        //buildBody.push_back(t_body);
    }
    return body;
}

b2Body *AJ_PhysxPrefab::createBoostItem(b2Vec2 loc, float r, void *data)
{
  b2BodyDef bodyDef;
  bodyDef.type = b2_staticBody;
  bodyDef.position = loc;
  bodyDef.userData = data;
  b2Body* body = B2Physx::the()->createBody(bodyDef);

  b2CircleShape dynamicCircle;
  dynamicCircle.m_p.Set(0,0);
  dynamicCircle.m_radius = r;
  b2FixtureDef fixtureDef;
  fixtureDef.shape = &dynamicCircle;
  fixtureDef.filter = filterBoostItem;
  fixtureDef.isSensor = true;
  body->CreateFixture(&fixtureDef);

  return body;
}

void AJ_PhysxPrefab::createCamera(b2Vec2 loc)
{
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position = loc;
  bodyDef.gravityScale = 0.0f;
  bodyDef.linearDamping = 3;
  b2Body* body = B2Physx::the()->createBody(bodyDef);
  cam =  body;
}

void AJ_PhysxPrefab::setCameraAim(b2Vec2 aimLoc)
{
  float x,y;
  getCameraPos(x,y);
  b2Vec2 cLoc(x,y);
  b2Vec2 force = aimLoc - cLoc;
  float v = force.Normalize();
  v = pow(v,2.8f);
  force *= v;
  cam->ApplyForce(force,b2Vec2(0,0),true);
}

void AJ_PhysxPrefab::getCameraPos(float &x, float &y)
{
  b2Transform tra = cam->GetTransform();
  x = tra.p.x;
  y = tra.p.y;
}
