#pragma once
#include "MovingObj.hpp"

class Power : public MovingObj
{
public :
    int ExistTime;
public :
    Power();
    ~Power();
    void Run();
};
