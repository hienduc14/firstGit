#pragma once
#include "MovingObj.hpp"
#include "Func.hpp"

const double EnemyCD = 500;
class Enemy : public MovingObj
{
public :
    double HP;
    double CoolDown = EnemyCD;
public :
    Enemy();
    ~Enemy();
    void Chase();
    void SetUp(int x, int y, int type);
};
