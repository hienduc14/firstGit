#pragma once
#include "../Enemy/Enemy.hpp"

class Exp : public Enemy
{
public :
    Exp();
    ~Exp();
    int stat = 1;
    int type = 1;
    // 1 exp; 2 coin;
};
