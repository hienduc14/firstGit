#include "Menu.hpp"

Menu::Menu()
{
//    Screen MainMenu;
    MainMenu.rectst = {0, 0, 1002, 564};
    MainMenu.rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    MainMenu.SetTexture(std::string("./menu/Menu.png"));

//    Button Play;
    Play.rectst = {0, 0, 403, 146};
    Play.rect = {CENTER_X-150, SCREEN_HEIGHT-200, 300, 95};
    Play.SetTexture(std::string("./menu/play.png"));

//  ThemeSound
    ThemeSound = Mix_LoadWAV("./asset/MenuTheme.WAV");
}

Menu::~Menu()
{

}

int Menu::play()
{

    Mix_PlayChannel(0, ThemeSound, -1);


    while( !Quit ){
        Play.status = 0;
        while(SDL_PollEvent(&base::g_event))
        {
            if (base::g_event.type == SDL_QUIT)
            {
                Quit = true;
                break;
            }
            Check();
        }
        if( MapChoice != -1 ){
            Mix_HaltChannel(-1);
            return MapChoice;
        }


        Draw();
        SDL_RenderPresent(base::renderer);
    }
    Mix_HaltChannel(-1);
    return 0;
}

void Menu::Draw()
{
    switch (MenuState)
    {
        case 0 :
        {
            MainMenu.drawObj();
            Play.drawObj();
            break;
        }
        case 1:
        {
            mapChoose.Draw();
            break;
        }
    }
}

void Menu::Check()
{
    switch (MenuState)
    {
        case 0 :
        {

            Play.CheckMouse(base::g_event);

            if( Play.status == 1 ) MenuState = 1;
            break;
        }
        case 1 :
        {
            MapChoice = mapChoose.play();
            break;
        }
    }
}
