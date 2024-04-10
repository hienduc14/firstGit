#include <SDL.h>
#include "Function/BasicFn/BasicFn.hpp"
#include "../gameplay/Game/Game.hpp"
#include "../menu/Menu.hpp"
#include "../menu/MapChoose.hpp"
int main( int argc, char* args[] )
{
    // khoi tao window, renderer...
    base::initSDL();
    Menu menu;
    srand(SDL_GetTicks());
    while( !Quit ){
        int state = menu.play();
        if( state == 1 ){
            MapChoose maps;
            int choice = maps.play();
            Game game;
            game.play( choice );
        }
    }
    // thoat chuong trinh
    base::quitSDL();
    return 0;
}
