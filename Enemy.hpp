#pragma once
#include "MovingObj.hpp"
#include "Func.hpp"
const std::string SlimeImg = "slime.png";
class Enemy : public MovingObj
{
public :
    int HP;
    int CoolDown;
public :
    Enemy();
    ~Enemy();
    void Chase();
    void SetUp(int x, int y, const std::string Pic);
};
