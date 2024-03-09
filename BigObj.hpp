#pragma once
#include "BasicFn.hpp"


class BigObj
{
protected :
    SDL_Rect rect;
    SDL_Texture* texture;
    SDL_Rect rectst;
public :
    // tao constructor va destructor
    BigObj();
    ~BigObj();

    // tao setter va getter cua rect va texture
    void SetRectSt(int x, int y);
    void SetRect(int x, int y);
    void SetTexture( const std::string filePath );

    SDL_Rect GetRectSt();
    SDL_Rect GetRect();
    SDL_Texture* GetTexture();

    // ve hinh anh tu texture
    void drawObj();
};
