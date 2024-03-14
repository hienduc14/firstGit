#pragma once
#include <SDL.h>
#include "BasicFn.hpp"
#include "Func.hpp"
#include "BigObj.hpp"
#include "Player.hpp"
#include "Screen.hpp"
#include "Enemy.hpp"
#include "Orb.hpp"
#include "FireBall.hpp"
#include "Exp.hpp"
#include "ImgTexture.hpp"
#include "Button.hpp"
const std::string PauseImg = "pause.png";
const std::string HomeImg = "home.png";
const std::string ResumeImg = "resume.png";
const std::string PauseMenuImg = "PauseMenu.png";
class Game
{
public :
    Game();
    ~Game();
private :
    Player player;
    std::list<Enemy> enemies;
    std::list<Orb> orbs;
    std::list<FireBall> fireBalls;
    std::list<Exp> exps;
    int frame = 0;
    Screen Map;
    Button pause;
    Button resume;
    Button home;
    Screen PauseMenu;
public :
    void play( int StartPower );

};
