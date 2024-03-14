#pragma once
#include "BasicFn.hpp"
#include "BigObj.hpp"
#include "Func.hpp"
class MovingObj : public BigObj
{
public :
    MovingObj();
    ~MovingObj();

protected :
    double a_x = 0, a_y = 0;
    double v_Obj = 0;
    double timeCurrent;
    double frameTime;
    int frameNum;
public :
    int damage = 0;
    bool exist = 0;
    int c_x, c_y;
public :
    void Change( double ax, double ay );
    void Located();
    void RenderMoving();
};
