#pragma once
#include <SDL.h>
#include "BasicFn.hpp"
#include "Func.hpp"
#include "BigObj.hpp"
#include "Player.hpp"
#include "Screen.hpp"
#include "Enemy.hpp"
#include "Power.hpp"
#include "Orb.hpp"
#include "Exp.hpp"
#include "ImgTexture.hpp"
#include "Button.hpp"
const std::string PauseImg = "pause.png";
const std::string HomeImg = "home.png";
const std::string ResumeImg = "resume.png";
const std::string PauseMenuImg = "PauseMenu.png";
namespace play
{
//    int frame = 0;
    void Game( int StartPower );
//    void KeyInput(Player &player);
//    void SpawnEnemy( std::list<Enemy> &enemies );
//    void HandlePower( Player &player, std::list<Orb> &orbs );

}
