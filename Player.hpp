#pragma once
#include "BasicFn.hpp"
#include "BigObj.hpp"
#include "Screen.hpp"
#include "Enemy.hpp"
#include "Orb.hpp"
#include "Exp.hpp"
#include "ImgTexture.hpp"
#include <vector>
#define PlayerWidth 196
#define PlayerHeight 137
#define HealthBarWidth 80
#define HealthBarHeight 10
#define PlayerR 100
class Player : public BigObj
{
public :
    Player();
    ~Player();
private :
    double a_x = 0, a_y = 0;
    double v_Player = 300;
    int dir = 0;
    bool MyPower[5] = {0, 0, 0, 0, 0};
    int Cycle[5] = {1, 0, 0, 0, 0};
    BigObj Health;
    BigObj HealthBar;
public :
    int HPMax = 30;
    int HP = 30;
    int ExpBar = 0;
public :
    void ResetInput();
    void KeyInput();
    void Move( Screen &Map, std::list<Enemy> &enemies, std::list<Orb> &orbs, std::list<Exp> &exps );
    void SetDir();
    int GetDir();
    void SetPower( int x );
    int GetPower( int x );
    void SetCycle( int x, int t );
    int GetCycle( int t );
    void SetHealthBar();
    void Bleeding( int dmg );
    void renderPlayer();
};
