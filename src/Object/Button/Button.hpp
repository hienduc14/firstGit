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
    int type = 0;
public :
    void CheckMouse(SDL_Event &e);

    void CheckTick(SDL_Event &e);
    void drawTick();

    SDL_Rect limit;
    int luu_x, luu_y;
    void CheckHold(SDL_Event &e);
    void drawHold();
};
