#include "Func.hpp"

int func::dist( int x, int y, int u, int v ){
//    std::cout << x << " " << y << " " << u << " " << v << '\n';
//    return 10;
    return sqrt( 1ll*(u-x)*(u-x) + 1ll*(v-y)*(v-y) );
}

bool func::checkRect( SDL_Rect rect1, SDL_Rect rect2 ){
    return ((rect1.x+rect1.w >= rect2.x) &&
            (rect2.x+rect2.w >= rect1.x) &&
            (rect1.y+rect1.w >= rect2.y) &&
            (rect2.y+rect2.w >= rect1.y) );
}
