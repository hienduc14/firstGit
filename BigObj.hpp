#pragma once
#include "BasicFn.hpp"


class BigObj
{
protected :
    SDL_Rect rect;
    SDL_Texture* texture;
public :
    // tao constructor va destructor
    BigObj();
    ~BigObj();

    // tao setter va getter cua rect va texture
    void SetRect(int x, int y, int w, int h){ this->rect = {x, y, w, h}; };
    SDL_Rect GetRect(){ return this->rect; };

    void SetTexture( std::string &filePath );
    SDL_Texture* GetTexture(){ return this->texture; };

    // ve hinh anh tu texture
    void drawObj();
};
