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
    if( base::CanChoose == true )
        if( RectOccupy.checkRect(base::CenterRect) ) dem++;
    return dem;
}

void Enemy::MoveOccupy( std::list<Enemy>& enemies )
{
    if( IsThrough == false ){
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
    else{
        double Dist = func::dist(aim_x, aim_y, c_x, c_y );
        if( Dist == 0 ) return;
        Change(( v_Obj*(aim_x-c_x)/Dist ), ( v_Obj*(aim_y-c_y)/Dist ) );
        Located();
    }
}

void Enemy::ChangeOccupy( double ax, double ay, std::list<Enemy>& enemies )
{
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

void Enemy::SetUp(int x, int y, int type){
    switch (type)
    {
        case -1:{
            texture = pre::ExpTexture;
            break;
        }
        case 0:{
            texture = pre::SlimeTexture;
//            clip[0] = {4, 8, 28-4, 28-8};
            clip[0].x = 0; clip[0].y = 0;
            SDL_QueryTexture(pre::SlimeTexture, NULL, NULL, &clip[0].w, &clip[0].h);
            clip[0].w /= pre::SlimeFrame;
            SetClip(0.1, pre::SlimeFrame, 1);
            break;
        }
        case 1:{
            texture = pre::RabbitTexture;
//            clip[0] = {47, 57, 80-47, 80-57};
            clip[0].x = 0; clip[0].y = 0;
            SDL_QueryTexture(pre::RabbitTexture, NULL, NULL, &clip[0].w, &clip[0].h);
            clip[0].w /= pre::RabbitFrame;
            SetClip(0.2, pre::RabbitFrame, 1);
            break;
        }
        case 2:{
            texture = pre::BoarTexture;
//            clip[0] = {29, 42, 67-29, 65-42};
            clip[0].x = 0; clip[0].y = 0;
            SDL_QueryTexture(pre::BoarTexture, NULL, NULL, &clip[0].w, &clip[0].h);
            clip[0].w /= pre::BoarFrame;
            SetClip(0.2, pre::BoarFrame, 1);
            break;
        }
        case 3:{
            texture = pre::BoarTexture;
//            clip[0] = {29, 42, 67-29, 65-42};
            clip[0].x = 0; clip[0].y = 0;
            SDL_QueryTexture(pre::BoarTexture, NULL, NULL, &clip[0].w, &clip[0].h);
            clip[0].w /= pre::BoarFrame;
            SetClip(0.2, pre::BoarFrame, 1);
            break;
        }
        case 4:{
            texture = pre::BoarTexture;
//            clip[0] = {29, 42, 67-29, 65-42};
            clip[0].x = 0; clip[0].y = 0;
            SDL_QueryTexture(pre::BoarTexture, NULL, NULL, &clip[0].w, &clip[0].h);
            clip[0].w /= pre::BoarFrame;
            SetClip(0.2, pre::BoarFrame, 1);
            break;
        }
    }
    exist = 1;
    rect.x = x; rect.y = y;
    Located();
    SetL();
}

void Enemy::SetClip( double x, int y, bool IsClipSet )
{
    timeCurrent = 0;
    frameTime = x; frameNum = y;
    SDL_QueryTexture(texture, NULL, NULL, &rectst.w, &rectst.h);
    int W = rectst.w/frameNum, H = rectst.h;
    if( IsClipSet == false ){
        for( int i = 0; i <= frameNum-1; i++ )
        {
            clip[i].w = W;
            clip[i].h = H;
            clip[i].x = W*i;
            clip[i].y = 0;
        }
    }
    else{
        for( int i = 1; i <= frameNum-1; i++ )
        {
            clip[i].w = clip[0].w;
            clip[i].h = clip[0].h;
            clip[i].x = clip[i-1].x+W;
            clip[i].y = clip[i-1].y;
        }
    }
    rect.w = clip[0].w; rect.h = clip[0].h;
}
