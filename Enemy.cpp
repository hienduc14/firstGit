#include "Enemy.hpp"

Enemy::Enemy()
{
    v_Obj = 3;
    damage = 1;
    HP = 4;
    CoolDown = 2;
    this->SetTexture(SlimeImg);
}

Enemy::~Enemy()
{

}



void Enemy::Chase(){
//    int Dist = func::dist(CENTER_X, CENTER_Y, rect.x+rect.w/2, rect.y+rect.h/2 );
//    int k = Dist/v_Obj;
//    Change( (CENTER_X-rect.x)/k, ((CENTER_Y-rect.y))/k );
    int ax=0, ay=0;
    if( rect.x < CENTER_X-rect.w/2 ) ax = v_Obj;
    if( rect.x > CENTER_X-rect.w/2 ) ax = -v_Obj;
    if( rect.y < CENTER_Y-rect.h/2 ) ay = v_Obj;
    if( rect.y > CENTER_Y-rect.h/2 ) ay = -v_Obj;
    Change( ax, ay );
}

void Enemy::SetUp(int x, int y){
    rectst = { 0, 0, 220, 150 };
    rect = { x, y, 60, 50 };
    exist = 1;
}
