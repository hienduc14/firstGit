#pragma once
#include "MovingObj.hpp"
#include "Func.hpp"
#define FireBallImgW 160
#define FireBallImgH 155
#define FireBallW 50
#define FireBallH 40
const double FireBallV = 100;
const double FireBallCD = 3000;

class FireBall : public MovingObj
{
public :
    double delayTime = 0;
public :
    int ExistTime;
public :
    FireBall();
    virtual ~FireBall();
    void Create();
    void Start( int u, int v, int x, int y );
    void Aim( int x, int y );
    void Run();
};

