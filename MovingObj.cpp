#include "MovingObj.hpp"

MovingObj :: MovingObj()
{
}

MovingObj :: ~MovingObj()
{

}

void MovingObj::Change( double ax, double ay )
{
    L_x += ax*TimeManager::Instance()->getElapsedTime()*GameSpeed;
    L_y += ay*TimeManager::Instance()->getElapsedTime()*GameSpeed;
    rect.x = L_x; rect.y = L_y;
    Located();
}

void MovingObj::Located()
{
    c_x = rect.x + rect.w/2;
    c_y = rect.y + rect.h/2;
}

void MovingObj::RenderMoving()
{
    timeCurrent += TimeManager::Instance()->getElapsedTime();
    while( timeCurrent >= frameTime*frameNum ) timeCurrent -= frameTime*frameNum;
//    if( timeCurrent < 5) timeCurrent ++; else timeCurrent = 0;
//    int clipIndex = timeCurrent;
//    rectst = clip[clipIndex];
    int clipIndex = timeCurrent/frameTime;
    rectst = clip[clipIndex];
    std::cout << clipIndex << '\n';
    double angle = func::GetAngle( a_x, a_y );

    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if( rect.x > CENTER_X ) flip = SDL_FLIP_VERTICAL;

    SDL_RenderCopyEx(base::renderer, texture, &clip[clipIndex], &rect, angle, nullptr, flip);
}
