#include "Orb.hpp"

Orb::Orb()
{
    damage = 2;
}

Orb::~Orb()
{

}

void Orb::Create()
{
    SetTexture(OrbImg);
    this->rectst.w = OrbImgW;
    this->rectst.h = OrbImgH;
    this->rect.w = OrbW;
    this->rect.h = OrbH;
    v_Obj = OrbV;
    exist = 1;
}

void Orb::Start( int dir, int x, int y )
{
    SetRect(CENTER_X-rect.w/2, CENTER_Y-rect.h/2);
    a_x = v_Obj*dx[dir];
    a_y = v_Obj*dy[dir];
};


