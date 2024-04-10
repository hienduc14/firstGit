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

void MovingObj::RenderMoving( bool IsMove, bool IsFlip, bool IsRotate )
{
    if( IsMove == false )
    {
        double angle = func::GetAngle( a_x, a_y );

        SDL_RendererFlip flip = SDL_FLIP_NONE;
        if( rect.x > CENTER_X ) flip = SDL_FLIP_HORIZONTAL;

        SDL_RenderCopyEx(base::renderer, texture, &rectst, &rect, angle, nullptr, flip);
    }
    else
    {
        //lay frame cua animation theo thoi gian
        timeCurrent += TimeManager::Instance()->getElapsedTime();
        while( timeCurrent >= frameTime*frameNum ) timeCurrent -= frameTime*frameNum;
        int clipIndex = timeCurrent/frameTime;
        //lay goc di chuyen
        double angle = func::GetAngle( a_x, a_y ) * IsRotate;

        //lay huong di chuyen
        SDL_RendererFlip flip = SDL_FLIP_NONE;
        if( IsFlip == true && rect.x > CENTER_X ) flip = SDL_FLIP_HORIZONTAL;

        SDL_RenderCopyEx(base::renderer, texture, &clip[clipIndex], &rect, angle, nullptr, flip);

        // gan lai frame hien tai
        rectst = clip[clipIndex];
    }
}
