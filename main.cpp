#include <SDL.h>
#include "BasicFn.hpp"
#include "BigObj.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include <iostream>
int main( int argc, char* args[] )
{
    // khoi tao window, renderer...
    base::initSDL();

    // ve map
    std::string x = "map.jpg";

    Map BackGr;
    Player player;

    bool quit = false;
    while(!quit)
    {
        while(SDL_PollEvent(&base::g_event))
        {
            if (base::g_event.type == SDL_QUIT)
            {
                quit = true;
                break;
            }

        }
        player.ResetInput();
        player.KeyInput(base::g_event);

        player.Move(BackGr);

        BackGr.drawObj();
        player.drawObj();

        SDL_RenderPresent(base::renderer);
        SDL_Delay( 10 );
    }


    SDL_Delay( 50000 );

    // thoat chuong trinh
    base::quitSDL();
    return 1;
}
