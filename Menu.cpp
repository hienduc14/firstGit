#include "Menu.hpp"

namespace play
{

}

int play::Menu()
{
    Screen MainMenu;
    MainMenu.rectst = {0, 0, 1002, 564};
    MainMenu.rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    MainMenu.SetTexture(MainMenuImg);
    Button Play;
    Play.rectst = {0, 0, 403, 146};
    Play.rect = {CENTER_X-150, SCREEN_HEIGHT-200, 300, 95};
    Play.SetTexture(PlayImg);
    while( !Quit ){
//            Play.status = 0;
        while(SDL_PollEvent(&base::g_event))
        {
            if (base::g_event.type == SDL_QUIT)
            {
                Quit = true;
                break;
            }
            Play.CheckMouse(base::g_event);
        }
        MainMenu.drawObj();
        Play.drawObj();
        SDL_RenderPresent(base::renderer);
        if( Play.status == 1 ) return 1;
    }
    return 0;
}
