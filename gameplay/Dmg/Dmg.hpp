#pragma once
#include "../../src/Object/TextObj/TextObj.hpp"
#include "../../asset/ImgTextLoad/ImgTextLoad.hpp"
class Dmg : public TextObj
{
private :
    SDL_Texture* Border;
public :
    bool exist = 1;
    double CurrentTime = 0;
    double FrameTime = 0.03;
    int FadeIn = 6; int Stay = 2; int FadeOut = 10;
    int FrameNum = FadeIn+Stay+FadeOut;
    bool HaveSound = false;
public :
    Dmg();
    Dmg(double num, int x, int y);
    ~Dmg();

    std::string NumToStr(double Num);
    void SetUp(std::string tex, int x, int y );
    void SetClip();
    void PopUp(bool IsMove);
    void Write(SDL_Rect, bool IsBorder);
};
