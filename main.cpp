#include <SDL.h>
#include "BasicFn.hpp"

int main( int argc, char* args[] )
{
    // khoi tao window, renderer...
    base::initSDL();

//    ve map
//    std::string x = "map.jpg";
//    SDL_Texture *BackGr = base::Load_Image(x);
    SDL_Texture *BackGr = base::Load_Image( std::string("map.jpg") );

    SDL_Rect Rect = {-500,-500, 1300, 1300};
    // Vẽ texture lên renderer tại tọa độ (x, y)
    SDL_RenderCopy(base::renderer, BackGr, NULL, &Rect);
    SDL_RenderPresent(base::renderer);

    SDL_Delay( 50000 );

    // thoat chuong trinh
    base::quitSDL();
}
