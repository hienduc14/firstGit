#include <SDL.h>
#include "BasicFn.hpp"
#include "Game.hpp"
#include "Menu.hpp"
#include "Button.hpp"
int main( int argc, char* args[] )
{
    // khoi tao window, renderer...
    base::initSDL();
    while( !Quit ){
        int state = play::Menu();
        if( state == 1 ) play::Game( 0 );
    }
    // thoat chuong trinh
    base::quitSDL();
    return 0;
}
