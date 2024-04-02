#include <SDL.h>
#include "BasicFn.hpp"
#include "Game.hpp"
#include "Menu.hpp"
#include "Button.hpp"
#include "TextObj.hpp"
#include "Dmg.hpp"
#include "Wave.hpp"
int main( int argc, char* args[] )
{
    // khoi tao window, renderer...
    base::initSDL();
    Menu menu;
    srand(SDL_GetTicks());
    while( !Quit ){
        int state = menu.play();
        if( state == 1 ){
            Game game;
            game.play( 0 );
        }
    }
    // thoat chuong trinh
    base::quitSDL();
    return 0;
}
