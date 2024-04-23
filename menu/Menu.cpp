#include "Menu.hpp"

Menu::Menu()
{
//    Screen MainMenu;
    MainMenu.SetTexture(std::string("./menu/Menu.png"));
    Blur.SetTexture(std::string("./menu/Blur.png"));
    ExitMenu.SetTexture(std::string("./menu/ExitMenu.png"));

//    Button Play;
    Play.SetTexture(std::string("./menu/play.png"));
    SDL_QueryTexture(Play.texture, nullptr, nullptr, &Play.rectst.w, &Play.rectst.h);
    Play.rect = {351, 350, 299, 69};

//    Button Shop
    Shop.SetTexture(std::string("./menu/Shop.png"));
    SDL_QueryTexture(Shop.texture, nullptr, nullptr, &Shop.rectst.w, &Shop.rectst.h);
    Shop.rect = {395, 458, 209, 69};

//    Button Collection
    Collection.SetTexture(std::string("./menu/Collection.png"));
    SDL_QueryTexture(Collection.texture, nullptr, nullptr, &Collection.rectst.w, &Collection.rectst.h);
    Collection.rect = {116, 458, 209, 69};

//    Button Tutorial
    Tutorial.SetTexture(std::string("./menu/Tutorial.png"));
    SDL_QueryTexture(Tutorial.texture, nullptr, nullptr, &Tutorial.rectst.w, &Tutorial.rectst.h);
    Tutorial.rect = {674, 458, 209, 69};

//    Button Options
    Options.SetTexture(std::string("./menu/Options.png"));
    SDL_QueryTexture(Options.texture, nullptr, nullptr, &Options.rectst.w, &Options.rectst.h);
    Options.rect = {917, 20, 63, 51};

//    Button Back
    Back.SetTexture(std::string("./menu/Back.png"));
    SDL_QueryTexture(Back.texture, nullptr, nullptr, &Back.rectst.w, &Back.rectst.h);
    Back.rect = {20, 20, 67, 57};

//    Button Exit
    Exit.SetTexture(std::string("./menu/Exit.png"));
    SDL_QueryTexture(Exit.texture, nullptr, nullptr, &Exit.rectst.w, &Exit.rectst.h);
    Exit.rect = {374, 420, 250, 68};

//    Button TickBox
    TickBox.SetTexture(std::string("./menu/TickBox.png"));
    SDL_QueryTexture(TickBox.texture, nullptr, nullptr, &TickBox.rectst.w, &TickBox.rectst.h);
    TickBox.rect = {596, 278, 38, 37};


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

        std::cout << DmgAppear << '\n';
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
            Shop.drawObj();
            Collection.drawObj();
            Tutorial.drawObj();
            Options.drawObj();
            break;
        }
        case 1:
        {
            mapChoose.Draw();
            break;
        }
        case 2:
        {
            Blur.drawObj();
            ExitMenu.drawObj();
            Exit.drawObj();
            Back.drawObj();
            TickBox.drawTick();
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
            Options.CheckMouse(base::g_event);
            if( Play.status == 1 ) MenuState = 1;
            if( Options.status == 1 ) MenuState = 2;
            break;
        }
        case 1 :
        {
            MapChoice = mapChoose.play();
            break;
        }
        case 2 :
        {
            Back.CheckMouse(base::g_event);
            Exit.CheckMouse(base::g_event);
            TickBox.CheckTick(base::g_event);
            if( Back.status == 1 ) MenuState = 0;
            if( Exit.status == 1 ) Quit = 1;
            if( TickBox.status == 1 ) DmgAppear = false;
            else DmgAppear = true;
            break;
        }
    }
}
