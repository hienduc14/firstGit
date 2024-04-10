#pragma once
#include <SDL.h>
//#include "BasicFn.hpp"
//#include "Func.hpp"
//#include "BigObj.hpp"
#include "../Player/Player.hpp"
//#include "Screen.hpp"
//#include "Enemy.hpp"
//#include "Orb.hpp"
//#include "FireBall.hpp"
//#include "Zone.hpp"
//#include "Exp.hpp"
#include "../LevelUp/Card/Card.hpp"
#include "../LevelUp/PowerUp/PowerUp.hpp"
//#include "ImgTexture.hpp"
//#include "Button.hpp"
#include "../Dmg/Dmg.hpp"
#include "../Detail/TimeCount.hpp"
#include "../Detail/KillCount.hpp"
#include "../Opponent/Wave/Wave.hpp"
//#include "Boss.hpp"
#include <utility>
class Game
{
public :
    Game();
    ~Game();
private :
    Player player;

    int MapTerrain;

    std::list<Enemy> enemies;
    Boss boss;

    std::list<Orb> orbs;
    std::list<FireBall> fireBalls;
    std::list<Exp> exps;
    std::list<Dmg> dmgs;
    Zone zone;
    Screen Map;
    Button pause;
    Button resume;
    Button home;
    Screen PauseMenu;
    Card card[3];
    std::pair<int, int> timeSpawn = {-2000, 1000};

    TimeCount timecount;
    KillCount killcount;

    Wave wave;
    std::pair<int, int> CurrentWave = {0, -1};
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
