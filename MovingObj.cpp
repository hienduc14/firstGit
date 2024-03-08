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
}

