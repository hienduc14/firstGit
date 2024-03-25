#include "TextObj.hpp"

TextObj::TextObj()
{

}

TextObj::~TextObj()
{

}

void TextObj::SetTTF( SDL_Texture* &TTFTexture )
{
    texture = TTFTexture;
    SDL_QueryTexture(texture, NULL, NULL, &rectst.w, &rectst.h);
    rectst.x = rectst.y = 0;
}
