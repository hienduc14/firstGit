#include "Menu.hpp"

Menu::Menu()
{
//    Screen MainMenu;
    MainMenu.SetTexture(std::string("./menu/Menu.png"));
    Blur.SetTexture(std::string("./menu/Blur.png"));
    ExitMenu.SetTexture(std::string("./menu/ExitMenu.png"));
    ShopMenu.SetTexture(std::string("./menu/Shop/ShopMenu.png"));
    TutorialMenu.SetTexture(std::string("./menu/TutorialMenu.png"));

//    Button Play;
    Play.SetTexture(std::string("./menu/play.png"));
    SDL_QueryTexture(Play.texture, nullptr, nullptr, &Play.rectst.w, &Play.rectst.h);
    Play.rect = {351, 458, 299, 69};

//    Button Shop
    Shop.SetTexture(std::string("./menu/Shop.png"));
    SDL_QueryTexture(Shop.texture, nullptr, nullptr, &Shop.rectst.w, &Shop.rectst.h);
    Shop.rect = {116, 458, 209, 69};

////    Button Collection
//    Collection.SetTexture(std::string("./menu/Collection.png"));
//    SDL_QueryTexture(Collection.texture, nullptr, nullptr, &Collection.rectst.w, &Collection.rectst.h);
//    Collection.rect = {116, 458, 209, 69};

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
    TickBox.status = 1-DmgAppear;
//    Sound Control
    SoundEFVolume.SetTexture(std::string("./menu/Volume.png"));
    SDL_QueryTexture(SoundEFVolume.texture, nullptr, nullptr, &SoundEFVolume.rectst.w, &SoundEFVolume.rectst.h);
    SoundEFVolume.rect = {389, 160, 225*SoundEFPer, 18};

    SoundEFPoint.SetTexture(std::string("./menu/VolumePoint.png"));
    SDL_QueryTexture(SoundEFPoint.texture, nullptr, nullptr, &SoundEFPoint.rectst.w, &SoundEFPoint.rectst.h);
    SoundEFPoint.limit = {387, 0, 217, 0};
    SoundEFPoint.rect = {SoundEFPoint.limit.x+SoundEFPoint.limit.w*SoundEFPer, 230-82, SoundEFPoint.rectst.w, SoundEFPoint.rectst.h };

    MusicVolume.SetTexture(std::string("./menu/Volume.png"));
    SDL_QueryTexture(MusicVolume.texture, nullptr, nullptr, &MusicVolume.rectst.w, &MusicVolume.rectst.h);
    MusicVolume.rect = {389, 242, 225*MusicPer, 18};

    MusicPoint.SetTexture(std::string("./menu/VolumePoint.png"));
    SDL_QueryTexture(MusicPoint.texture, nullptr, nullptr, &MusicPoint.rectst.w, &MusicPoint.rectst.h);
    MusicPoint.limit = {387, 0, 217, 0};
    MusicPoint.rect = {MusicPoint.limit.x+MusicPoint.limit.w*MusicPer, 230, MusicPoint.rectst.w, MusicPoint.rectst.h };

//    ShopMenu
    SkinChoice[0].SetTexture(std::string("./menu/Shop/Skin0Bought.png"));
    SkinChoice[0].QuerySetup();
    SkinChoice[0].rect = {157, 163, 104, 96};
    for( int i = 1; i < NumChoice; i++ ){
        if( SkinBought[i] == false ){
            std::string u = "./menu/Shop/Skin1.png";     u[16] = char(i+'0');
            SkinChoice[i].SetTexture(u);
            SkinChoice[i].QuerySetup();
            SkinChoice[i].rect = {157+(104+30)*i, 163, 104, 96};
            SkinChoice[i].CanPress = 0;
        }else
        {
            std::string u = "./menu/Shop/Skin1Bought.png";     u[16] = char(i+'0');
            SkinChoice[i].SetTexture(u);
            SkinChoice[i].QuerySetup();
            SkinChoice[i].rect = {157+(104+30)*i, 163, 104, 96};
            SkinChoice[i].CanPress = true;
        }
    }
    for( int i = 0; i < NumChoice; i++ ){
        if( SkinBought[i] == false ){
            Buy[i].SetTexture(std::string("./menu/Shop/Buy.png"));
            Buy[i].QuerySetup();
            Buy[i].rect = SkinChoice[i].rect;
            Buy[i].rect = { Buy[i].rect.x + Buy[i].rect.w/2 - Buy[i].rectst.w/2,
                            Buy[i].rect.y + Buy[i].rect.h +10,
                            Buy[i].rectst.w,
                            Buy[i].rectst.h };
            Buy[i].CanPress = 1;
        }else{
            Buy[i].SetTexture(std::string("./menu/Shop/Buy.png"));
            Buy[i].QuerySetup();
            Buy[i].rect = SkinChoice[i].rect;
            Buy[i].rect = { Buy[i].rect.x + Buy[i].rect.w/2 - Buy[i].rectst.w/2,
                            Buy[i].rect.y + Buy[i].rect.h +10,
                            Buy[i].rectst.w,
                            Buy[i].rectst.h };
            Buy[i].CanPress = 0;
        }
    }
    Buy[0].CanPress = 0;

    Used.SetTexture(std::string("./menu/Shop/Used.png"));
    Used.QuerySetup();
    Used.rect = Buy[SkinOption].rect;

    CoinFont = TTF_OpenFont("./menu/Shop/FreshMan.ttf", 35);


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
            Shop.drawObj();
//            Collection.drawObj();
            Tutorial.drawObj();
            Options.drawObj();
            break;
        }
        case 1:
        {
            mapChoose.Draw();
            Back.drawObj();
            break;
        }
        case 2:
        {
            Blur.drawObj();
            ExitMenu.drawObj();
            Exit.drawObj();
            Back.drawObj();
            TickBox.drawTick();

            SoundEFVolume.drawObj();
            MusicVolume.drawObj();

            SoundEFPoint.drawHold();
            MusicPoint.drawHold();
            break;
        }
        case 3:
        {
            //shop
            Blur.drawObj();
            ShopMenu.drawObj();
            Back.drawObj();
            for( int i = 0; i < NumChoice; i++ ) SkinChoice[i].drawChoice();
            for( int i = 0; i < NumChoice; i++ ) if( Buy[i].CanPress == 1 ) Buy[i].drawChoice();

            std::string CoinNum = std::to_string(Coin) + " $";
            CoinShow.SetTTF(CoinNum, 0, 0, CoinFont, Black );
            CoinShow.rect.x = 1000 - 20 - CoinShow.rectst.w;
            CoinShow.rect.y = 20;
            CoinShow.drawObj();
            std::cout << SkinOption << '\n';
            Used.drawObj();
//            for( int i = 0; i < NumChoice; i++ ) std::cout << SkinBought[i] << " "; std::cout << '\n';
            break;
        }
        case 4 :
        {
            Blur.drawObj();
            Back.drawObj();
            TutorialMenu.drawObj();
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
            if( Play.status == 1    ) MenuState = 1;

            Options.CheckMouse(base::g_event);
            if( Options.status == 1 ) MenuState = 2;

            Shop.CheckMouse(base::g_event);
            if( Shop.status ==   1    ) MenuState = 3;

            Tutorial.CheckMouse(base::g_event);
            if( Tutorial.status ==   1    ) MenuState = 4;
            break;
        }
        case 1 :
        {
            MapChoice = mapChoose.play();

            Back.CheckMouse(base::g_event);
            if( Back.status == 1 ) MenuState = 0;

            break;
        }
        case 2 :
        {
            Back.CheckMouse(base::g_event);
            if( Back.status == 1 ) MenuState = 0;

            Exit.CheckMouse(base::g_event);
            if( Exit.status == 1 ) Quit = 1;

            TickBox.CheckTick(base::g_event);
            if( TickBox.status == 1 ) DmgAppear = false;
            else DmgAppear = true;

            SoundEFPoint.CheckHold(base::g_event);
            MusicPoint.CheckHold(base::g_event);
            double per1 = double(SoundEFPoint.rect.x - SoundEFPoint.limit.x)/SoundEFPoint.limit.w;
            double per2 = double(MusicPoint.rect.x - MusicPoint.limit.x)/MusicPoint.limit.w;
            SoundEFVolume.rect.w = per1*SoundEFVolume.rectst.w;
            MusicVolume.rect.w = per2*MusicVolume.rectst.w;

            SoundEFPer = per1;
            MusicPer = per2;
            Mix_Volume(1, MIX_MAX_VOLUME*SoundEFPer);
            Mix_Volume(0, MIX_MAX_VOLUME*MusicPer);

            break;
        }
        case 3 :
        {
            Back.CheckMouse(base::g_event);
            if( Back.status == 1 ) MenuState = 0;

            for( int i = 0; i < NumChoice; i++ ) if( SkinChoice[i].CanPress == true ) {
                SkinChoice[i].CheckMouse(base::g_event);
                if( SkinChoice[i].status == 1 ) SkinOption = i;
                Used.rect = Buy[SkinOption].rect;
            }
            for( int i = 0; i < NumChoice; i++ ) if( Buy[i].CanPress == true ) {
                int test = 1;
                Buy[i].CheckChoice(base::g_event, test, 0);
                if( test != Buy[i].CanPress && Coin >= BuyCost[i] )
                {
                    Buy[i].CanPress = test;
                    // minus cost
                    Coin -= BuyCost[i];

                    // change skinoption to bought
                    std::string u = "./menu/Shop/Skin1Bought.png";     u[16] = char(i+'0');
                    SkinChoice[i].SetTexture(u);
                    SkinChoice[i].CanPress = true;
                    SkinBought[i] = true;
                    base::UpdateData();
                }
            }

            break;
        }
        case 4 :
        {
            Back.CheckMouse(base::g_event);
            if( Back.status == 1 ) MenuState = 0;
            break;
        }
    }
}
