#pragma once
#include "../../../asset/ImgTextLoad/ImgTextLoad.hpp"
#include "../../../src/Object/MovingObj/MovingObj.hpp"

class Kameha : public MovingObj
{
public :
    Kameha();
    virtual ~Kameha();

public :
    int state = 0; bool IsStateChange = false;
    // 0 ko co gi 1 chuan bi 2 phong

    double angle = 0;
    SDL_Point startPoint;
    int Dis = 30;

    double StartRelease = 0, EndRelease = 5000;

    void SetUp( int type );
    void Aim( int x, int y, double goc );
    void Firing( bool IsMoving);
    int CheckDmg( SDL_Rect target );
    int StartDmg = 0, EndDmg = 500;
};
