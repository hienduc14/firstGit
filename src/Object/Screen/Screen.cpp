#include "Screen.hpp"

Screen::Screen()
{
    this->rectst = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    this->rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SetL();
}

Screen::~Screen()
{

}

void Screen::SetMap()
{
    texture = pre::MapTexture;
    SDL_QueryTexture(texture, NULL, NULL, &MapWidth, &MapHeight);
    MapWidth/=3; MapHeight/=3;
    rectst = {0, 0, MapWidth*3, MapHeight*3};
    rect = {-MapWidth, -MapHeight, MapWidth*3, MapHeight*3};
    SetL();
}

void Screen::MapMove(double u, double v){
    L_x += u*TimeManager::Instance()->getElapsedTime();
    L_y += v*TimeManager::Instance()->getElapsedTime();
    rect.x = L_x; rect.y = L_y;
    if( this->rect.x >= 0 ) this->rect.x-=MapWidth;
    if( this->rect.y >= 0 ) this->rect.y-=MapHeight;
    if( this->rect.x <= -MapWidth*2 ) this->rect.x+=MapWidth;
    if( this->rect.y <= -MapHeight*2 ) this->rect.y+=MapHeight;

    if( L_x >= 0 ) L_x-=MapWidth;
    if( L_y >= 0 ) L_y-=MapHeight;
    if( L_x <= -MapWidth*2 ) L_x+=MapWidth;
    if( L_y <= -MapHeight*2 ) L_y+=MapHeight;
}
