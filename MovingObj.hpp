#pragma once
#include "BasicFn.hpp"
#include "BigObj.hpp"
class MovingObj : public BigObj
{
public :
    MovingObj();
    ~MovingObj();

protected :
    int a_x = 0, a_y = 0;
    int v_Obj = 0;
public :
    int damage = 0;
    bool exist = 0;
public :
    void Change( int ax, int ay );
//    void Run();
};
