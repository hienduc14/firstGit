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
#include "Zone.hpp"
#include "Exp.hpp"
#include "Card.hpp"
#include "PowerUp.hpp"
#include "ImgTexture.hpp"
#include "Button.hpp"
#include <utility>
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
    Zone zone;
    Screen Map;
    Button pause;
    Button resume;
    Button home;
    Screen PauseMenu;
    Card card[3];
    std::pair<int, int> timeSpawn = {-2000, 1000};
public :
    void play( int StartPower );
    void Prepare();
    void LevelUp();
    void SpawnEnemy();
    void Firing();
    void PowerColision();
    void PowerExisted();
    void PauseGame();
    void RenderGamePlay( int IsMoving );
    void RemoveThing();
};
