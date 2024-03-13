#pragma once
#include "BasicFn.hpp"
#include "Screen.hpp"
#include "Button.hpp"

const std::string MainMenuImg = "Menu.png";
const std::string PlayImg = "play.png";
extern Screen MainMenu;
extern Button Play;

namespace play
{
    int Menu();
}

