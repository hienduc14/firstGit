#include <SDL.h>
#include "BasicFn.hpp"
#include "BigObj.hpp"

int main( int argc, char* args[] )
{
    // khoi tao window, renderer...
    base::initSDL();

//    ve map
    std::string x = "map.jpg";

    BigObj Map;
    Map.SetRect( 0, 0, 1000, 1000 );
    Map.SetTexture( x );
    Map.drawObj();
    SDL_RenderPresent(base::renderer);
    SDL_Delay( 50000 );

    // thoat chuong trinh
    base::quitSDL();
}
