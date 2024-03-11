#include "Enemy.hpp"

Enemy::Enemy()
{
    v_Obj = 3;
    damage = 1;
    HP = 4;
    CoolDown = 2;
    rectst = { 0, 0, 220, 150 };
    rect.w = 60; rect.h = 50;
}

Enemy::~Enemy()
{

}



void Enemy::Chase(){
    float Dist = func::dist(CENTER_X, CENTER_Y, rect.x+rect.w/2, rect.y+rect.h/2 );
    if( Dist == 0 ) return;
    float bt = 1;
    float ax = ( bt*(CENTER_X-rect.x)*v_Obj/Dist );
    float ay = ( bt*(CENTER_Y-rect.y)*v_Obj/Dist );
    Change( int(ax), int(ay) );
//    int ax=0, ay=0;
//    if( c_x < CENTER_X ) ax = v_Obj;
//    if( c_x > CENTER_X ) ax = -v_Obj;
//    if( c_y < CENTER_Y ) ay = v_Obj;
//    if( c_y > CENTER_Y ) ay = -v_Obj;
//    Change( ax, ay );
    Located();
}

void Enemy::SetUp(int x, int y, const std::string Pic){
    exist = 1;
    rect.x = x; rect.y = y;
    this->SetTexture(Pic);
    Located();
}
