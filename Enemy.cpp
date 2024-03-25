#include "Enemy.hpp"
Enemy::Enemy()
{
    v_Obj = 30;
    damage = 5;
    HP = 4;
    this->rectst.w = EnemyW;
    this->rectst.h = EnemyH;
    this->rect.w = 50;
    this->rect.h = 50;
    L_x = rect.x; L_y = rect.y;
    timeCurrent = 0;
    frameTime = 0.1; frameNum = 10;
    for( int i = 0; i <= frameNum-1; i++ )
    {
        clip[i].w = EnemyImgW;
        clip[i].h = EnemyImgH;
        clip[i].x = EnemyImgW*i;
        clip[i].y = 0;
    }
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

void Enemy::SetOccupy()
{
    RectOccupy = {L_x, L_y, rect.w, rect.h};
    RectOccupy.x += 8; RectOccupy.w -= 8;
    RectOccupy.y += 8; RectOccupy.h -= 8;
}

int Enemy::CheckOccupy( std::list<Enemy>& enemies )
{
    int dem = 0;
    for( auto enemy : enemies )
        if( RectOccupy.checkArea( enemy.RectOccupy ) ) dem++;
    return dem;
}

void Enemy::MoveOccupy( std::list<Enemy>& enemies )
{
    double Dist = func::dist(CENTER_X, CENTER_Y, c_x, c_y );
    if( Dist == 0 ) return;
    double ax = v_Obj*(CENTER_X-c_x)/Dist;
    double ay = v_Obj*(CENTER_Y-c_y)/Dist;
    double preL_x = L_x, preL_y = L_y;
    L_x += ax*TimeManager::Instance()->getElapsedTime()*GameSpeed;
    rect.x = L_x;
    SetOccupy();
    Located();

    if( CheckOccupy( enemies ) > 1 )
    {
        L_x = preL_x;
        rect.x = L_x;
        SetOccupy();
        Located();
    }
    L_y += ay*TimeManager::Instance()->getElapsedTime()*GameSpeed;
    rect.y = L_y;
    SetOccupy();
    Located();
    if( CheckOccupy( enemies ) > 1 )
    {
        L_y = preL_y;
        rect.y = L_y;
        SetOccupy();
        Located();
    }
}

