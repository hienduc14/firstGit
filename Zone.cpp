#include "Zone.hpp"

Zone::Zone()
{
    damage = ZoneDmg;
    this->rectst.w = ZoneImgW;
    this->rectst.h = ZoneImgH;
    this->rect.w = ZoneW;
    this->rect.h = ZoneH;
    exist = 1;
}

Zone::~Zone()
{

}

void Zone::Start()
{
    switch (CanDmg)
    {

    case -1 :
        this->texture = pre::ZoneTexture;
        SetRect(CENTER_X-rect.w/2, CENTER_Y-rect.h/2);
        Located();
        SetL();
        CanDmg = 1;
        break;
    case 0 :
        CanDmg = 1;
    }
}

bool Zone::DOT( Enemy &enemy )
{
    bool ok = 0;
    if( func::dist( CENTER_X, CENTER_Y, enemy.c_x, enemy.c_y ) <= radius+20 )
    {
        if(enemy.IsDot == 0){
            enemy.HP -= damage;
            ok = 1;
        }
        enemy.IsDot += TimeStep;
        if(enemy.IsDot > delay) enemy.IsDot = 0;

    }
    return ok;
}

bool Zone::DOT( Boss &boss )
{
    bool ok = 0;
    if( func::dist( CENTER_X, CENTER_Y, boss.c_x, boss.c_y ) <= radius+100 )
    {
        if(boss.IsDot == 0){
            boss.HP -= damage;
            ok = 1;
        }
        boss.IsDot += TimeStep;
        if(boss.IsDot > delay) boss.IsDot = 0;

    }
    return ok;
}
