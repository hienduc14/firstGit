#pragma once
#include "../../src/Object/TextObj/TextObj.hpp"
#include "../../asset/ImgTextLoad/ImgTextLoad.hpp"
class KillCount : public TextObj
{
private :
    int Count = 0;
public :
    SDL_Color color = Black;
public :
    KillCount();
    ~KillCount();

    void Add();
    void Display();
};
