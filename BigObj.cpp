#pragma once
#include "BigObj.hpp"

BigObj::BigObj(){
    rect = {0, 0, 0, 0};
    texture = nullptr;
}

BigObj::~BigObj(){
    if( texture != nullptr ){
        delete texture;
        texture = nullptr;
    }
}

void BigObj::drawObj()
{
    SDL_RenderCopy(base::renderer, texture, NULL, &rect);
}
void BigObj::SetTexture( std::string &filePath )
{
    texture = base::Load_Image( filePath );
}
