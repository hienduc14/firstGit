#pragma once
#include "../BigObj/BigObj.hpp"
#include "../../../asset/ImgTextLoad/ImgTextLoad.hpp"
class Button : public BigObj
{
public :
    Button();
    ~Button();
public :
    int status = 0;
public :
    void CheckMouse(SDL_Event e);
};
