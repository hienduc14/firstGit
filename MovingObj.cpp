#include "MovingObj.hpp"

MovingObj :: MovingObj()
{

}

MovingObj :: ~MovingObj()
{

}

void MovingObj::Change( int ax, int ay )
{
    this->rect.x += ax; this->rect.y += ay;
    Located();
}

void MovingObj::Located(){
    c_x = rect.x + rect.w/2;
    c_y = rect.y + rect.h/2;
}
