#include "FireBall.hpp"

FireBall::FireBall()
{
    damage = 10;
    ExistTime = 10000;
    this->texture = pre::FireBallTexture;
    this->rectst.w = FireBallW;
    this->rectst.h = FireBallH;
    this->rect.w = 80;
    this->rect.h = 30;
    v_Obj = FireBallV;
    exist = 1;
    timeCurrent = 0;
    frameTime = 0.05; frameNum = 8;
    for( int i = 0; i <= frameNum-1; i++ )
    {
        clip[i].w = FireBallW;
        clip[i].h = FireBallH;
        clip[i].x = FireBallW*i;
        clip[i].y = 0;
    }
}

FireBall::~FireBall()
{

}

void FireBall::Create()
{

}

void FireBall::Start( int x, int y )
{
    SetRect(CENTER_X-rect.w/2, CENTER_Y-rect.h/2);
    Located();
    SetL();
//    L_x = rect.x; L_y = rect.y;
    Aim( x, y );

};

void FireBall::Aim( int x, int y ){
    double Dist = func::dist(CENTER_X, CENTER_Y, x, y );
    if( Dist == 0 ) return;
    a_x = v_Obj*(x-c_x)/Dist;
    a_y = v_Obj*(y-c_y)/Dist;
    Located();
}
void FireBall::Run(){
    Change( a_x, a_y );
}


