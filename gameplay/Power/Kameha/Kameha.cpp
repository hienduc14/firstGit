#include "Kameha.hpp"

Kameha::Kameha()
{
    damage = 100;
}

Kameha::~Kameha()
{

}

void Kameha::SetUp( int type )
{
    switch (type)
    {
        //nguoi choi
        case 0 :
        {
            if( state == 2 ){
                texture = pre::KamehaTexture;
                frameNum = 5;
                frameTime = 0.1;
                int W, H;
                SDL_QueryTexture(texture, NULL, NULL, &W, &H);
                W = W/frameNum;
                for( int i = 0; i < frameNum; i++ )
                {
                    clip[i] = { W*i, 0, W, H };
                }
                timeCurrent = 0;
//                rect = { CENTER_X + 30, CENTER_Y-H/2, W, H };
            }
            else
            if( state == 1 ){
                texture = pre::AimArrowTexture;
                frameNum = 1;
                frameTime = 0.1;
                int W, H;
                SDL_QueryTexture(texture, NULL, NULL, &W, &H);
                W = W/frameNum;
                for( int i = 0; i < frameNum; i++ )
                {
                    clip[i] = { W*i, 0, W, H };
                }
                timeCurrent = 0;
//                rect = { CENTER_X + 30, CENTER_Y-H/2, W, H };
            }
            break;
        }

        //boss
        case 1 :
        {
            if( state == 2 ){
                texture = pre::BossKamehaTexture;
                frameNum = 8;
                frameTime = 0.1;
                int W, H;
                SDL_QueryTexture(texture, NULL, NULL, &W, &H);
                W = W/frameNum;
                for( int i = 0; i < frameNum; i++ )
                {
                    clip[i] = { W*i, 0, W, H };
                }
                timeCurrent = 0;
//                rect = { CENTER_X + 30, CENTER_Y-H/2, W, H };
            }
            else
            if( state == 1 ){
                texture = pre::BossAimArrowTexture;
                frameNum = 1;
                frameTime = 0.1;
                int W, H;
                SDL_QueryTexture(texture, NULL, NULL, &W, &H);
                W = W/frameNum;
                for( int i = 0; i < frameNum; i++ )
                {
                    clip[i] = { W*i, 0, W, H };
                }
                timeCurrent = 0;
//                rect = { CENTER_X + 30, CENTER_Y-H/2, W, H };
            }
            break;
        }
    }
}

void Kameha::Aim(int x, int y, double goc)
{
    startPoint.x = x;
    startPoint.y = y;
//    angle = (goc/180)*M_PI;
    angle = goc;
    rect = { x + 30, y-clip[0].h/2, clip[0].w, clip[0].h };
//    std::cout << x << " " << y << " " << goc << '\n';
}

void Kameha::Firing()
{
    if(state == 1 )
    {
        timeCurrent += TimeManager::Instance()->getElapsedTime();
        while( timeCurrent >= frameTime*frameNum ) timeCurrent -= frameTime*frameNum;
        int clipIndex = timeCurrent/frameTime;
        SDL_Point centerPoint = { startPoint.x - rect.x, startPoint.y - rect.y };
        SDL_RenderCopyEx(base::renderer, texture, &clip[clipIndex], &rect, angle, &centerPoint, SDL_FLIP_NONE);

    }
    else
    if( state == 2 )
    {
        if( startPoint.x == CENTER_X && startPoint.y == CENTER_Y ){
            timeCurrent += TimeManager::Instance()->getElapsedTime();
            while( timeCurrent >= frameTime*frameNum ) timeCurrent -= frameTime*frameNum;
            int clipIndex = timeCurrent/frameTime;
            SDL_Point centerPoint = { startPoint.x - rect.x, startPoint.y - rect.y };
            SDL_RenderCopyEx(base::renderer, texture, &clip[clipIndex], &rect, angle, &centerPoint, SDL_FLIP_NONE);
        }
        else{
            timeCurrent += TimeManager::Instance()->getElapsedTime();
            while( timeCurrent >= frameTime*frameNum ) timeCurrent -= frameTime*frameNum;
            int clipIndex = timeCurrent/frameTime;
            SDL_Point centerPoint = { startPoint.x - rect.x, startPoint.y - rect.y };

//            SDL_Rect nR = rect;
//            if( nR.x < 0 - 50 ){
//                    nR.x +=
//            }
            SDL_RenderCopyEx(base::renderer, texture, &clip[clipIndex], &rect, angle, &centerPoint, SDL_FLIP_NONE);
        }
    }

    if( state == 2 ) {
        StartDmg += TimeStep;
        if( StartDmg >= EndDmg) StartDmg = 0;
    }else StartDmg = 0;


    angle = std::fmod(std::fmod(angle, 360) + 360, 360);
}

int Kameha::CheckDmg( SDL_Rect target )
{
    int x, y, r;
    x = target.x + target.w/2;
    y = target.y + target.h/2;
    r = (target.w/2 > target.h/2 ? target.h/2 : target.w/2);

    // sin = opposite side/hypotenuse
    double hypotenuse = func::dist( x, y, startPoint.x, startPoint.y );
    double targetAngle = func::GetAngle(x-startPoint.x, y-startPoint.y);
    if( targetAngle < 0 ) targetAngle += 360;
    double angleDis = angle - targetAngle;

    if( angleDis < 0 ) angleDis = -angleDis;
    if( angleDis > 90 ) return 0;

    double opSide = sin(angleDis*M_PI/180)*hypotenuse;
    double adjSide = sqrt(hypotenuse*hypotenuse - opSide*opSide);
    if( opSide < r +rect.h/2 && adjSide > Dis ){
        if( StartDmg == 0 ){
            std::cout << angleDis << '\n';
            return damage;
        }
        return 0;
    }
    else return 0;
}
