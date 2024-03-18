#pragma once
#include "MovingObj.hpp"
#include "Func.hpp"
#include "Enemy.hpp"
#define ZoneImgW 519
#define ZoneImgH 519
#define ZoneW 300
#define ZoneH 300

class Zone : public MovingObj
{
private :
    int radius = 150;
public :
    Zone();
    virtual ~Zone();
    void Start();
    void DOT( Enemy &enemy );
};
