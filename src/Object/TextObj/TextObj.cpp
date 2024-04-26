#include "TextObj.hpp"

TextObj::TextObj()
{

}

TextObj::~TextObj()
{

}

void TextObj::SetTTF(std::string tex, int x, int y, TTF_Font* font, SDL_Color color)
{
    SDL_DestroyTexture(texture);
    texture = base::Load_Text(tex, font, color);
    SDL_QueryTexture(texture, NULL, NULL, &rectst.w, &rectst.h);
    rectst.x = rectst.y = 0;
    rect.x = x; rect.y = y;
    rect.w = rectst.w; rect.h = rectst.h;
}
