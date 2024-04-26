#include <SDL.h>
#include "Function/BasicFn/BasicFn.hpp"
#include "../gameplay/Game/Game.hpp"
#include "../menu/Menu.hpp"
#include "../asset/ImgTextLoad/ImgTextLoad.hpp"
int main( int argc, char* args[] )
{
    // khoi tao window, renderer...
    base::initSDL();
    srand(SDL_GetTicks());
    base::GetData();
    LoadAll preload;
    preload.loading();
    while( !Quit ){
        Menu menu;
        int state = menu.play();
        if( Quit ) break;
        Game game;
        game.play( state );
    }
    base::UpdateData();
    preload.release();
    // thoat chuong trinh
    base::quitSDL();
    return 0;
}
