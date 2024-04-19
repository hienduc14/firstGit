#pragma once
#include "../BasicFn/BasicFn.hpp"
#include <valarray>
#include <utility>
#include <cmath>
namespace func
{
    // lay khoang cach
    double dist( int x, int y, int u, int v );
    // va cham
    bool checkRect( SDL_Rect rect1, SDL_Rect rect2 );
    // lay ngau nhien trong x->y
    int random( int x, int y );
    // lay goc theo toa do
    double GetAngle( double x, double y );
    // lay toa do theo goc
    std::pair<int, int> GetPosCircle( double angle, double R );
}

struct Area
{
    double x, y; int w, h;
    bool checkArea( Area rect );
    bool checkRect( SDL_Rect rect);
};
