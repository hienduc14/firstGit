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
    delayTime = 0;
}

Orb::~Orb()
{

}

void Orb::Create()
{

}

void Orb::Start( int dir, int x, int y )
{
    SetRect(x-rect.w/2, y-rect.h/2);
    a_x = v_Obj*dx[dir];
    a_y = v_Obj*dy[dir];
    if( a_x && a_y )
    {
        a_x /= 1.414;
        a_y /= 1.414;
    }
    L_x = rect.x; L_y = rect.y;
};
void Orb::Run(){
    Change( a_x, a_y );
}
