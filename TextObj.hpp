#pragma once
#include "BasicFn.hpp"
#include "BigObj.hpp"

class TextObj : public BigObj
{
public :
    TextObj();
    ~TextObj();
public :
    void SetTTF( SDL_Texture* &TTFTexture );
};
