#pragma once
#include "BasicFn.hpp"
#include "BigObj.hpp"
#include "Screen.hpp"
#include "Enemy.hpp"
#include "Orb.hpp"
#include "FireBall.hpp"
#include "Exp.hpp"
#include "ImgTexture.hpp"
#include <vector>
#define PlayerWidth 196
#define PlayerHeight 137
#define HealthBarWidth 80
#define HealthBarHeight 10
#define ExpBarWidth 80
#define ExpBarHeight 10
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
    int MyPower[5] = {0, 0, 0, 0, 0};
    double CD[5] = {1*1000, 3*1000, 3*1000, 0, 0};
    double StartCD[5] = {-1, -1, -1, -1, -1};
    int ExpRequire[10] = { 1, 10, 15, 20, 25, 30, 35, 40, 45, 50 };
    BigObj Health;
    BigObj HealthBar;
    BigObj ExpPoint;
    BigObj ExpBar;
public :
    int HPMax = 30;
    int HP = 30;
    int EXP = 0;
    int Level = 0;
public :
    void SetUp();
    void ResetInput();
    void KeyInput();
    void Move( Screen &Map, std::list<Enemy> &enemies, std::list<Orb> &orbs, std::list<FireBall> &fireBalls, std::list<Exp> &exps );
    void SetDir();
    int GetDir();
    void SetPower( int x );
    int GetPower( int x );
    void SetCD( int x, int t );
    int GetCD( int t );
    void SetStartCD( int x );
    int GetStartCD( int t );
    void SetHealthBar();
    void SetExpBar();
    void Bleeding( int dmg );
    int ExpAbsorb( Exp &exp );
    void renderPlayer();
    int checkCD( int t );
};
