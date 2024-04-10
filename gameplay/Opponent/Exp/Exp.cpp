#include "Exp.hpp"

Exp::Exp()
{
    exist = 1;
    v_Obj = 300;
    rectst.x = 0; rectst.y = 0;
    rectst.w = 400; rectst.h = 400;
    rect.w = 52; rect.h = 52;
    texture = pre::ExpTexture;
    Located();
}

Exp::~Exp()
{

}
