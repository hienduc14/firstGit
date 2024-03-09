#pragma once
#include "MovingObj.hpp"
#include "Func.hpp"
const std::string SlimeImg = "slime_walk.png";
class Enemy : public MovingObj
{
public :
    Enemy();
    ~Enemy();
    void Chase();
    void SetUp(int x, int y);
};
