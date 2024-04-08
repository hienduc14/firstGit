#pragma once
#include "Enemy.hpp"
const double BossCD = 500;

class Boss : public Enemy
{
public :
    Boss();
    ~Boss();
public :
    int phaseState;
    // 0 di chuyen // 1 nhay // 2 dam chan
    SDL_Rect phaseRect[5][10];
    int NumF = 0;
    std::pair<int, double> phaseFrame[5] = { {4, 0.1}, {2, 0.1}, {1, 0.1}, {7, 0.1}, {6, 0.15} };
    double phaseTime[5] = { 0.5, 0.2, 3, 0.7, 5 };
    // 0 prepare; 1 jumping; 2 floating; 3 landing; 4 moving

    double ExistTime = 0;
    double v_Fly;
    int dmgSkill; bool SkillHit = false;
    int aim_x, aim_y;

    int IsDot = 0;
    double CoolDown = BossCD;
public:
    void SetUp( int x, int y );
    void SetState();
    void SetPhaseClip();
    void Doing();
    SDL_Rect GetBossBody();
};

