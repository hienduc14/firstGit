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
    void Draw();
    void Check();

    Screen MainMenu;
    Button Play;
    Mix_Chunk* ThemeSound = nullptr;
private :
    MapChoose mapChoose;
    int MapChoice = -1;

public :
    int play();
};

