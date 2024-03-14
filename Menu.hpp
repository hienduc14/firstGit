#pragma once
#include "BasicFn.hpp"
#include "Screen.hpp"
#include "Button.hpp"

const std::string MainMenuImg = "Menu.png";
const std::string PlayImg = "play.png";

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

