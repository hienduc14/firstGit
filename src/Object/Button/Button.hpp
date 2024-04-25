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
    bool CanPress = 1;
public :
    void QuerySetup();

    void CheckMouse(SDL_Event &e);

    void CheckTick(SDL_Event &e);
    void drawTick();

    SDL_Rect limit;
    int luu_x, luu_y;
    void CheckHold(SDL_Event &e);
    void drawHold();

    void CheckChoice(SDL_Event &e, int &NeedChange, int Changed);
    void drawChoice();
};
