#pragma once
#include "../../Function/BasicFn/BasicFn.hpp"
#include "../BigObj/BigObj.hpp"
#include "../../Function/Func/Func.hpp"
#include "../../TimeManage/Time.hpp"
class MovingObj : public BigObj
{
public :
    MovingObj();
    ~MovingObj();
protected :
    double a_x = 0, a_y = 0;
    double timeCurrent;
    double frameTime;
    int frameNum;
public :
    double v_Obj = 0;
public :
    double damage = 0;
    bool exist = 0;
    int c_x, c_y;
public :
    void Change( double ax, double ay );
    void Located();
    void RenderMoving( bool IsMove, bool IsFlip, bool IsRotate );
};
