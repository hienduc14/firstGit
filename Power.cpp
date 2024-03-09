#include "Power.hpp"

Power::Power()
{
    rect.x = 0; rect.y = 0;
    v_Obj = 10;
}

Power::~Power()
{

}

void Power::SetType( int x )
{
    TypePower = x;
    SetTexture(ammo[x]);
    this->rectst.x = 0;
    this->rectst.y = 0;
    this->rectst.w = ammo_w[x];
    this->rectst.h = ammo_h[x];
    this->rect.w = 30;
    this->rect.h = 30;
    exist = 1;
}

int Power::GetType(){ return TypePower; }

void Power::Start( int dir, int x, int y )
{
    SetRect(CENTER_X + x*dx[dir], CENTER_Y + y*dy[dir]);
    a_x = v_Obj*dx[dir];
    a_y = v_Obj*dy[dir];

};

void Power::Run(){
    Change( a_x, a_y );
//    this->rect.x += a_x; this->rect.y += a_y;
    std::cout << rect.x << " " << rect.y << " " << rect.w << " " << rect.h << '\n';
    std::cout << a_x << " " << a_y << '\n';
}

