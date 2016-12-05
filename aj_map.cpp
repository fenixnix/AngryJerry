#include "aj_map.h"
#include "noise/noise.h"
#include "aj_physxprefab.h"
#include <map>
#include <unit.h>
#include "Render/nglrender.h"
#include "nfmodmngr.h"
#include "b2objunitmanager.h"
#include "physx/mrb2datamanager.h"

AJ_Map* AJ_Map::pStatic = nullptr;
noise::module::Perlin plNoise;
noise::module::Perlin enemyNoise;

map<int, b2Fixture*> scences;
map<int, vector<b2Fixture*>* > scencePlates;

void clearScencePlates(int i){
    //cout<<__FUNCTION__<<__LINE__<<endl;
    for(auto itr = scencePlates[i]->begin();itr!=scencePlates[i]->end();itr++){
        //cout<<__FUNCTION__<<__LINE__<<endl;
        B2Physx::the()->worldBase->DestroyFixture(*itr);
        //cout<<__FUNCTION__<<__LINE__<<endl;
    }
    //cout<<__FUNCTION__<<__LINE__<<endl;
    scencePlates[i]->clear();
    //cout<<__FUNCTION__<<__LINE__<<endl;
    delete scencePlates[i];
    //cout<<__FUNCTION__<<__LINE__<<endl;
    scencePlates.erase(scencePlates.find(i));
    //cout<<__FUNCTION__<<__LINE__<<endl;
}


AJ_Map::AJ_Map()
{
    scenceUnitWidth = 64;
    currentIndex = 0;
    scences.clear();
}

AJ_Map *AJ_Map::the()
{
    if(pStatic==nullptr){
        pStatic = new AJ_Map;
    }
    return pStatic;
}

void AJ_Map::init(int seed)
{
    plNoise.SetSeed (seed);
    plNoise.SetFrequency (1.0);
    plNoise.SetOctaveCount (2);
    //    plNoise.SetPersistence(0.01);
    //    mapNoise.SetNoiseQuality (QUALITY_STD);
}

#include "gaia/nixgaiatype.h"
void AJ_Map::render()
{
  NGLRender* render = NGLRender::the();
  render->useTex(nixgaia::SOIL);
  render->setMode(MODE_TEX);
  float src[12] = {};
  float uv[8] = {0,0,0,1,1,0,1,1};
  //N order
  for(float i = currentIndex*scenceUnitWidth - scenceUnitWidth;
      i<currentIndex*scenceUnitWidth+scenceUnitWidth;
      i+=0.5){
      src[0] = i;
      src[1] = -1;
      src[2] = 0;

      src[3] = src[0];
      src[4] = getValue(i);
      src[5] = src[2];

      src[6] = i+0.5;
      src[7] = src[1];
      src[8] = src[2];

      src[9] = src[6];
      src[10] = getValue(i+0.5);
      src[11] = src[2];
      render->drawTextrue(src,uv);
      src[0] = i;
      src[1] = -2;
      src[2] = 0;

      src[3] = src[0];
      src[4] = -1;
      src[5] = src[2];

      src[6] = i+0.5;
      src[7] = src[1];
      src[8] = src[2];

      src[9] = src[6];
      src[10] = src[4];
      src[11] = src[2];
      render->drawTextrue(src,uv);
    }

}

void AJ_Map::release()
{
    scences.clear();
    B2Physx::the()->clearWall();
}

float AJ_Map::getValue(float x)
{
    double value = plNoise.GetValue(x,0.5,0.5)*0.3;
    //cout<<value<<endl;
    return value;
}

void AJ_Map::generateEnemy(float x, int index)
{
    if(x>(scenceUnitWidth/3)){

        double value = plNoise.GetValue(x,0.5,0.5)*0.3;
///
        B2Unit *unit;
        b2Filter filterEnemy;
        filterEnemy.categoryBits = 0x0002;
        filterEnemy.maskBits = 0x000b;
        filterEnemy.groupIndex = -4;
///

        //cout<<__FUNCTION__<<value<<endl;
        if(value>0.2){
            //cout<<__FUNCTION__<<__LINE__<<endl;
            int enemyType = rand()%3;
            switch(enemyType){
            case 0: Unit::create("shooter",x,2);break;
            case 1: Unit::create("runner",x,5);
///
                unit = B2ObjUnitManager::the()->createB2Unit("beetle",b2Transform(b2Vec2(x,10),b2Rot(0)));
                unit->setAllFilter(filterEnemy);
                MRb2DataManager::the()->initB2UnitShapeData(unit);
///
                break;
            case 2: Unit::create("grenadiers",x,5);break;
            default:break;
            }
            //create enemy plate

            b2Fixture * w1 = AJ_PhysxPrefab::the()->createEnemyWall(b2Vec2(x-0.5,getValue(x)+value*10),b2Vec2(x-0.5,getValue(x)+value*10+0.3));
            b2Fixture * w2 = AJ_PhysxPrefab::the()->createEnemyWall(b2Vec2(x-0.5,getValue(x)+value*10),b2Vec2(x+0.5,getValue(x)+value*10));
            //cout<<__FUNCTION__<<__LINE__<<"*"<<currentIndex<<endl;
            if(scencePlates.find(index)== scencePlates.end()){
                cout<<"!!!!"<<__LINE__<<endl;
            }
            scencePlates[index]->push_back(w1);
            scencePlates[index]->push_back(w2);
            //cout<<__FUNCTION__<<__LINE__<<endl;
        }
    }
}

void AJ_Map::updatePos(float x)
{
    if(x>(currentIndex*scenceUnitWidth+scenceUnitWidth/2)){
        currentIndex++;
        generate(currentIndex);

    }
}

void AJ_Map::generate(int index)
{
    //delete all useless scences
    //cout<<__FUNCTION__<<__LINE__<<"*"<<scences.size()<<endl;
    currentIndex = index;
    for(auto itr = scences.begin();itr!=scences.end();){
        int id = itr->first;
        bool finded = false;
        for(int i = index - 1;i<=index+1;i++){
            if(id == i){
                finded = true;
                break;
            }
        }
        if(!finded){
            cout<<"destory index:"<<id<<endl;
            B2Physx::the()->worldBase->DestroyFixture(itr->second);
            clearScencePlates(id);
            itr = scences.erase(itr);
        }else{
            itr++;
        }
    }

//    cout<<"left size:"<<scences.size()<<endl;
//    for(auto itr = scences.begin();itr!=scences.end();itr++){
//        cout<<itr->first<<endl;
//    }

    //add empty ground
    for(int i = index - 1;i<=index+1;i++){
        auto itr = scences.find(i);
        if(itr == scences.end()){
            cout<<__FUNCTION__<<"create index:"<<i<<endl;
            scencePlates[i] = new vector<b2Fixture*>;
            vector<b2Vec2> points;
            for(int x = i*scenceUnitWidth-scenceUnitWidth/2;x<=i*scenceUnitWidth+scenceUnitWidth/2;x++){
                //cout<<__FUNCTION__<<__LINE__<<endl;
                points.push_back(b2Vec2(x,getValue(x)));
                //cout<<__FUNCTION__<<__LINE__<<endl;
                points.push_back(b2Vec2((float)x+0.5,getValue((float)x+0.5f)));
                //cout<<__FUNCTION__<<__LINE__<<endl;
                generateEnemy(x,i);
                //cout<<__FUNCTION__<<__LINE__<<endl;
            }
            //cout<<__FUNCTION__<<points.size()<<endl;
            scences[i] = B2Physx::the()->createBlockWalls(points.data(),points.size());
        }
    }
    //cout<<__FUNCTION__<<__LINE__<<"*"<<scences.size()<<endl;
}
