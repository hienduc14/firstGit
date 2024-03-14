#pragma once
#include "MovingObj.hpp"
#define OrbImgW 64
#define OrbImgH 60
#define OrbW 30
#define OrbH 30
const double OrbV = 500;
class Orb : public MovingObj
{
public :
    int ExistTime;
public :
    Orb();
    virtual ~Orb();
    void Create();
    void Start( int dir, int x, int y );
    void Run();
};
