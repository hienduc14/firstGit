#pragma once
#include "../src/Function/BasicFn/BasicFn.hpp"
#include "../src/Object/Screen/Screen.hpp"
#include "../src/Object/Button/Button.hpp"
#include "../src/Object/TextObj/TextObj.hpp"
#include "MapChoose.hpp"

class Menu
{
public :
    Menu();
    ~Menu();
private :
    int MenuState = 0;
//    bool ExitGame = false;
    void Draw();
    void Check();
    //MenuState 0
    Screen MainMenu;
    Button Play;
    Button Shop;
//    Button Collection;
    Button Tutorial;
    Button Options;

    //MenuState != 0
    Screen Blur;
    Button Back;

    //MenuState 2 Options
    Screen ExitMenu;
    Button Exit;
    Button TickBox;
    BigObj SoundEFVolume;
    Button SoundEFPoint;
    BigObj MusicVolume;
    Button MusicPoint;
    Mix_Chunk* ThemeSound = nullptr;

    //MenuState 3 Shop
    Screen ShopMenu;
    int NumChoice = 2;
    Button SkinChoice[4];
    bool IsBought[4] = {1, 0, 0, 0};
    Button Buy[4];
    int BuyCost[4] = { 10, 10, 10, 10 };
    Button Used;

    TTF_Font* CoinFont;
    TextObj CoinShow;

    //Menustate 4 tutorial
    Screen TutorialMenu;
private :
    MapChoose mapChoose;
    int MapChoice = -1;

public :
    int play();
};

