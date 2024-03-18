#pragma once
#include "MovingObj.hpp"
#include "Func.hpp"
//#define FireBallImgW 153
//#define FireBallImgH 10

#define FireBallImgW 160
#define FireBallImgH 155
#define FireBallW 160
#define FireBallH 155
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
