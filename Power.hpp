#pragma once
#include "MovingObj.hpp"




class Power : public MovingObj
{
public :
    Power();
    ~Power();
private :
    int TypePower;
    const char* ammo[4] = {"orb.png"};
    const int ammo_w[4] = { 64, 0, 0, 0 };
    const int ammo_h[4] = { 60, 0, 0, 0 };
public :
    void SetType(int x);
    int GetType();
    void Start( int dir, int x, int y );
    void Run();
};
