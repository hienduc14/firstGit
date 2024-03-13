#include "Enemy.hpp"
Enemy::Enemy()
{
    v_Obj = 30;
    damage = 5;
    HP = 4;
    rectst = { 0, 0, 220, 150 };
    rect.w = 60; rect.h = 50;
    L_x = rect.x; L_y = rect.y;
}

Enemy::~Enemy()
{

}



void Enemy::Chase(){
    double Dist = func::dist(CENTER_X, CENTER_Y, c_x, c_y );
    if( Dist == 0 ) return;
    Change(( v_Obj*(CENTER_X-c_x)/Dist ), ( v_Obj*(CENTER_Y-c_y)/Dist ) );
    Located();
}

void Enemy::SetUp(int x, int y, int type){
    if( type == 0 ) texture = pre::ExpTexture;
    if( type == 1 ) texture = pre::SlimeTexture;
    exist = 1;
    rect.x = x; rect.y = y;
    Located();
    SetL();
}
