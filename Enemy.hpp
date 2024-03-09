#pragma once
#include "MovingObj.hpp"
#include "Func.hpp"

class Enemy : public MovingObj
{
public :
    Enemy();
    ~Enemy();
    void Chase();
    void SetUp(int x, int y);
};
