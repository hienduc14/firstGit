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
    if( func::dist( CENTER_X, CENTER_Y, enemy.c_x, enemy.c_y ) <= radius+20 )
    {
        enemy.HP -= damage;
        return 1;
    }
    return 0;
}
