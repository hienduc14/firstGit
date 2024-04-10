#pragma once
#include "../../Function/BasicFn/BasicFn.hpp"
#include "../BigObj/BigObj.hpp"

class TextObj : public BigObj
{
public :
    TextObj();
    ~TextObj();
public :
    void SetTTF(std::string tex, int x, int y, TTF_Font* font, SDL_Color color);
};
