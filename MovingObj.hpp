#pragma once
#include "BasicFn.hpp"
#include "BigObj.hpp"
class MovingObj : public BigObj
{
public :
    MovingObj();
    ~MovingObj();

protected :
    double a_x = 0, a_y = 0;
    double v_Obj = 0;
public :
    int damage = 0;
    bool exist = 0;
    int c_x, c_y;
public :
    void Change( double ax, double ay );
    void Located();
//    void Run();
};
