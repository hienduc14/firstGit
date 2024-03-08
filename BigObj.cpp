#include "BigObj.hpp"

BigObj::BigObj(){
    rectst = {0, 0, 0, 0};
    rect = {0, 0, 0, 0};
    texture = nullptr;
}

BigObj::~BigObj(){
    if( texture != nullptr ){
        delete texture;
        texture = nullptr;
    }
}
void BigObj::SetRectSt(int x, int y){this->rectst.x = x; this->rectst.y = y;}
void BigObj::SetRect(int x, int y){this->rect.x = x; this->rect.y = y;}
void BigObj::SetTexture( const char* filePath ){texture = base::Load_Image( filePath );}

SDL_Rect BigObj::GetRectSt(){ return this->rectst; }
SDL_Rect BigObj::GetRect(){ return this->rect; }
SDL_Texture* BigObj::GetTexture(){ return this->texture; }


void BigObj::drawObj()
{
    SDL_RenderCopy(base::renderer, texture, &rectst, &rect);
}
