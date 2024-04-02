#include "Func.hpp"

double func::dist( int x, int y, int u, int v )
{
    return sqrt( 1ll*(u-x)*(u-x) + 1ll*(v-y)*(v-y) );
}

bool func::checkRect( SDL_Rect rect1, SDL_Rect rect2 )
{
    return ((rect1.x+rect1.w >= rect2.x) &&
            (rect2.x+rect2.w >= rect1.x) &&
            (rect1.y+rect1.w >= rect2.y) &&
            (rect2.y+rect2.w >= rect1.y) );
}

int func::random( int x, int y )
{
    return x + rand() % (y - x + 1);

}

double func::GetAngle(double x, double y)
{
    return atan2(y, x)*180/M_PI;
}

bool Area::checkArea( Area rect )
{
    return ((rect.x+rect.w >= x) &&
            (x+w >= rect.x) &&
            (rect.y+rect.w >= y) &&
            (y+w >= rect.y) );
}

bool Area::checkRect( SDL_Rect rect )
{
    return ((rect.x+rect.w >= x) &&
            (x+w >= rect.x) &&
            (rect.y+rect.w >= y) &&
            (y+w >= rect.y) );
}
