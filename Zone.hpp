#pragma once
#include "MovingObj.hpp"
#include "Func.hpp"
#include "Enemy.hpp"
#define ZoneImgW 519
#define ZoneImgH 519
#define ZoneR 90
#define ZoneW ZoneR*2
#define ZoneH ZoneR*2
const double ZoneCD = 500;
const double ZoneDmg = 2;
class Zone : public MovingObj
{
public:
    int radius = ZoneR;
    int CanDmg = -1;
    int CurrentLevel = 0;
    int delay = 1000;
public:
    Zone();
    virtual ~Zone();
    void Start();
    bool DOT( Enemy &enemy );
};
