#pragma once
#include "BasicFn.hpp"
#include <cmath>
namespace func
{
    // lay khoang cach
    float dist( int x, int y, int u, int v );
    // va cham
    bool checkRect( SDL_Rect rect1, SDL_Rect rect2 );
    // lay ngau nhien trong x->y
    int random( int x, int y );
}
