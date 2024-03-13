#pragma once
#include "BasicFn.hpp"
#include "ImgTexture.hpp"

class BigObj
{
public :
    SDL_Rect rect;
    SDL_Texture* texture;
    SDL_Rect rectst;
    double L_x = 0, L_y = 0;
    SDL_Rect frame_state[10];
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

    void SetL();

    // ve hinh anh tu texture
    void drawObj();
};
