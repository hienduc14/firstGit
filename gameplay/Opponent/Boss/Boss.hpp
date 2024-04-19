#pragma once
#include "../Enemy/Enemy.hpp"
const double BossCD = 500;

class Boss : public Enemy
{
public :
    Boss();
    ~Boss();
public :
    int BossType;

    int phaseState;
    SDL_Rect phaseRect[10][10];
    int NumPhase, NumF = 0;
    std::pair<int, double> phaseFrame[10];
    double phaseTime[10];

    double ExistTime = 0;
    double v_Fly;
    double a_x_Fly, a_y_Fly;
    int dmgSkill; bool SkillHit = false;
    int aim_x, aim_y;

    int IsDot = 0;
    double CoolDown = BossCD;

    int SummonWave = 0;
public:
    void SetUp( int x, int y, int type );
    void SetState();
    void SetPhaseClip();
    void Doing();
    SDL_Rect GetBossBody();
};

