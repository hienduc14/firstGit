#pragma once
#include "Enemy.hpp"

const std::string ExpImg = "exp.png";
class Exp : public Enemy
{
public :
    Exp();
    ~Exp();
    int stat = 0;
};
