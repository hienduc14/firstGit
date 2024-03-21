#include "Screen.hpp"

Screen::Screen()
{
    this->rectst = {0, 0, MapWidth, MapHeight};
    this->rect = {0, 0, MapWidth, MapHeight};
    SetL();
}

Screen::~Screen()
{

}

void Screen::MapMove(double u, double v){
    L_x += u*TimeManager::Instance()->getElapsedTime();
    L_y += v*TimeManager::Instance()->getElapsedTime();
    rect.x = L_x; rect.y = L_y;
    if( this->rect.x >= 0 ) this->rect.x-=MapWidth;
    if( this->rect.y >= 0 ) this->rect.y-=MapHeight;
    if( this->rect.x <= -MapWidth*2 ) this->rect.x+=MapWidth;
    if( this->rect.y <= -MapHeight*2 ) this->rect.y+=MapHeight;
    SetL();
}
