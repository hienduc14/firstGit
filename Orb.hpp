#pragma once
#include "Power.hpp"
#define OrbImgW 64
#define OrbImgH 60
#define OrbW 30
#define OrbH 30
#define OrbV 5
const std::string OrbImg = "orb.png";

class Orb : public Power
{
public :
    Orb();
    ~Orb();
    void Create();
    void Start( int dir, int x, int y );

};
