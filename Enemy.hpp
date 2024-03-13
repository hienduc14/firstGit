#pragma once
#include "MovingObj.hpp"
#include "Func.hpp"

const double EnemyCD = 2000;
class Enemy : public MovingObj
{
public :
    int HP;
    double CoolDown = EnemyCD;
public :
    Enemy();
    ~Enemy();
    void Chase();
    void SetUp(int x, int y, int type);
};
