#pragma once
#include "BasicFn.hpp"
#include "BigObj.hpp"
#include "Screen.hpp"
#include "Enemy.hpp"
#include "Boss.hpp"
#include "Orb.hpp"
#include "FireBall.hpp"
#include "Zone.hpp"
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
    double v_Player = 100;
    int ExpRequire[10] = { 1, 10, 15, 20, 25, 30, 35, 40, 45, 50 };
    BigObj Health;
    BigObj HealthBar;
    BigObj ExpPoint;
    BigObj ExpBar;
public :
    double HPMax = 30;
    double HP = 30;
    double EXP = 0;
    int Level = 0;
    int MyPower[5] = {0, 0, 0, 0, 0};
    double StartCD[5] = {-1, -1, -1, -1, -1};
    double CD[5] = {1*1000, FireBallCD, ZoneCD, 0, 0};
    int dir = 0;
    double Defense = 1;
    double ExpGain = 1;
public :
    void SetUp();
    void ResetInput();
    void KeyInput();
    void Move( Screen &Map, std::list<Enemy> &enemies, std::list<Orb> &orbs, std::list<FireBall> &fireBalls, std::list<Exp> &exps, Boss &boss );

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
