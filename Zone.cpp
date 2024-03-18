#include "Zone.hpp"

Zone::Zone()
{
    damage = 3;

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
    this->texture = pre::ZoneTexture;
    SetRect(CENTER_X-rect.w/2, CENTER_Y-rect.h/2);
    Located();
    SetL();
}

void Zone::DOT( Enemy &enemy )
{
    if( func::dist( CENTER_X, CENTER_Y, enemy.c_x, enemy.c_y ) <= radius )
        enemy.HP -= damage;
}
