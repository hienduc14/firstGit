#include "Enemy.hpp"

Enemy::Enemy()
{
    v_Obj = 1;
    this->SetTexture("slime_walk.png");
}

Enemy::~Enemy()
{

}

void Enemy::Chase(){
//    int Dist = func::dist(CENTER_X, CENTER_Y, this->rect.x+this->rect.w/2, this->rect.y+this->rect.h/2 );
//    int k = Dist/v_Obj;
//    Change( (CENTER_X-rect.x)/k, ((CENTER_Y-rect.y))/k );
    int ax=0, ay=0;
    if( rect.x < CENTER_X ) ax = v_Obj;
    if( rect.x > CENTER_X ) ax = -v_Obj;
    if( rect.y < CENTER_Y ) ay = v_Obj;
    if( rect.y > CENTER_Y ) ay = -v_Obj;
    Change( ax, ay );
}

void Enemy::SetUp(){
    rectst = { 0, 0, 220, 150 };
    rect = { 0, 0, 60, 50 };
}
