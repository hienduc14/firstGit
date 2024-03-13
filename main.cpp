#include <SDL.h>
#include "BasicFn.hpp"
#include "Game.hpp"
#include "Button.hpp"
const std::string MainMenuImg = "Menu.png";
const std::string PlayImg = "play.png";
int main( int argc, char* args[] )
{
    // khoi tao window, renderer...
    base::initSDL();
    Screen MainMenu;
    MainMenu.rectst = {0, 0, 1002, 564};
    MainMenu.rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    MainMenu.SetTexture(MainMenuImg);
    Button Play;
    Play.rectst = {0, 0, 403, 146};
    Play.rect = {CENTER_X-150, SCREEN_HEIGHT-200, 300, 95};
    Play.SetTexture(PlayImg);

    bool GameQuit = false;
    while( !GameQuit ){
        while(SDL_PollEvent(&base::g_event))
        {
            if (base::g_event.type == SDL_QUIT)
            {
                GameQuit = true;
                break;
            }
        }
        MainMenu.drawObj();
        Play.drawObj();
        SDL_RenderPresent(base::renderer);

        Play.CheckMouse(base::g_event);
        std::cout << Play.status << '\n';
        if( Play.status == 1 ) play::Game( 0 );
    }

    // thoat chuong trinh
    base::quitSDL();
    return 0;
}
