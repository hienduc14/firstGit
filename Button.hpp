#pragma once
#include "BigObj.hpp"

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
