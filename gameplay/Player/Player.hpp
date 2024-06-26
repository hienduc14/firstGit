#pragma once
#include "../../src/Function/BasicFn/BasicFn.hpp"
#include "../../src/Object/BigObj/BigObj.hpp"
#include "../../src/Object/Screen/Screen.hpp"

#include "../../asset/ImgTextLoad/ImgTextLoad.hpp"

#include "../Opponent/Enemy/Enemy.hpp"
#include "../Opponent/Boss/Boss.hpp"
#include "../Power/Orb/Orb.hpp"
#include "../Power/FireBall/FireBall.hpp"
#include "../Power/Zone/Zone.hpp"
#include "../Opponent/Exp/Exp.hpp"
#include "../Power/Kameha/Kameha.hpp"

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
    int ExpRequire[10] = { 1, 5, 6, 8, 9, 12, 13, 15, 15, 15 };
    BigObj Health;
    BigObj HealthBar;
    BigObj ExpPoint;
    BigObj ExpBar;

public :
    //rect collision
    SDL_Rect Body;

public :
    int aimDir;
    Kameha kameha;
    std::pair<int, int> JumpCD = {0, 3000};
    std::pair<int, int> KamehaCD = {0, 60000};
public :
    //animation
    int phaseState, NumPhase = 3, NumF = 0;
    // 0 standing 1 moving 2 jumping
    SDL_Rect phaseRect[10][10];
    std::pair<int, double> phaseFrame[10];
    double frameTime;
    int frameNum;
    double timeCurrent;
    std::pair<double,double> FlyTime = {0, 1000};
    double v_Stand = 0;
    double v_Move = 100;
    double v_Jump = 400;
    bool IsFlip = false;
    void SetState();
    void SetPhaseClip();
    void Print( bool IsMoving );
    std::pair<double, double> IsKame = {0, 1000};
public :
    double HPMax = 30;
    double HP = 30;
    double EXP = 0;
    int Level = 0;
    int MyPower[5] = {0, 0, 0, 0, 0};
    double StartCD[5] = {-1, -1, -1, -1, -1};
    double CD[5] = {1, FireBallCD/1000, ZoneCD/1000, 0, 0};
    int dir = 0;
    double Defense = 1;
    double ExpGain = 1;
public :
    void SetUp();
    void ResetInput();
    void KeyInput();
    void Move( double &ax, double &ay );

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
    void renderPlayer( bool IsMoving );
    int checkCD( int t );
};
