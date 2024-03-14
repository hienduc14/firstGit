#pragma once
#include "MovingObj.hpp"
#include "Func.hpp"
#define FireBallImgW 153
#define FireBallImgH 10
#define FireBallW 250
#define FireBallH 97
const double FireBallV = 100;

class FireBall : public MovingObj
{
public :
    int ExistTime;
public :
    FireBall();
    virtual ~FireBall();
    void Create();
    void Start( int x, int y );
    void Aim( int x, int y );
    void Run();
};
