#include <SDL.h>
#include "Function/BasicFn/BasicFn.hpp"
#include "../gameplay/Game/Game.hpp"
#include "../menu/Menu.hpp"
#include "../menu/MapChoose.hpp"
int main( int argc, char* args[] )
{
    // khoi tao window, renderer...
    base::initSDL();
    srand(SDL_GetTicks());
    while( !Quit ){
        Menu menu;
        int state = menu.play();
        Game game;
        game.play( state );
    }
    // thoat chuong trinh
    base::quitSDL();
    return 0;
}
