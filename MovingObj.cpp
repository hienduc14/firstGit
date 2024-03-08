#include "MovingObj.hpp"

MovingObj :: MovingObj()
{

}

MovingObj :: ~MovingObj()
{

}

void MovingObj::Change( int ax, int ay )
{
    this->a_x += ax; this->a_y += ay;
}

void MovingObj::Run(){
    rect.x += a_x; rect.y += a_y;
    a_x = 0; a_y = 0;
}
