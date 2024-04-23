#pragma once
#include "../src/Function/BasicFn/BasicFn.hpp"
#include "../src/Object/Screen/Screen.hpp"
#include "../src/Object/Button/Button.hpp"
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
    Button Collection;
    Button Tutorial;
    Button Options;

    //MenuState != 0
    Screen Blur;
    Button Back;

    //MenuState 1
    Screen ExitMenu;
    Button Exit;
    Button TickBox;
    BigObj SoundEFVolume;
    Button SoundEFPoint;
    BigObj MusicVolume;
    Button MusicPoint;
    Mix_Chunk* ThemeSound = nullptr;
private :
    MapChoose mapChoose;
    int MapChoice = -1;

public :
    int play();
};

