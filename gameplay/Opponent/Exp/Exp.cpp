#include "Exp.hpp"

Exp::Exp()
{
    exist = 1;
    v_Obj = 300;
    Located();
}

Exp::~Exp()
{
    texture = nullptr;
}
