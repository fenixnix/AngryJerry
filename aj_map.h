#ifndef AJ_MAP_H
#define AJ_MAP_H

class AJ_Map
{
public:
    AJ_Map();
    static AJ_Map *the();
    void init(int seed);
    void render();
    void release();
    float getValue(float x);
    void generateEnemy(float x,int index);
    void updatePos(float x);
    void generate(int index = 0);
    int forwardFlag;
    int backwordFlag;
private:
    static AJ_Map* pStatic;
    int scenceUnitWidth;
    int currentIndex;
};

#endif // AJ_MAP_H
