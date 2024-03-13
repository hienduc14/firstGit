#include "Orb.hpp"

Orb::Orb()
{
    damage = 2;
    ExistTime = 2000;
    this->texture = pre::OrbTexture;
    this->rectst.w = OrbImgW;
    this->rectst.h = OrbImgH;
    this->rect.w = OrbW;
    this->rect.h = OrbH;
    v_Obj = OrbV;
    exist = 1;
}

Orb::~Orb()
{

}

void Orb::Create()
{

}

void Orb::Start( int dir, int x, int y )
{
    SetRect(CENTER_X-rect.w/2, CENTER_Y-rect.h/2);
    a_x = v_Obj*dx[dir];
    a_y = v_Obj*dy[dir];
    L_x = rect.x; L_y = rect.y;
};
void Orb::Run(){
    Change( a_x, a_y );
}


