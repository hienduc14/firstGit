#pragma once
#include "../src/Function/BasicFn/BasicFn.hpp"
#include "../src/Object/Screen/Screen.hpp"
#include "../src/Object/Button/Button.hpp"


class Menu
{
public :
    Menu();
    ~Menu();
private :
    Screen MainMenu;
    Button Play;
public :
    int play();
};

