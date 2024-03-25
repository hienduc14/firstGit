#pragma once
#include "MovingObj.hpp"
#include "Func.hpp"
#define EnemyImgW 32
#define EnemyImgH 32
#define EnemyW 50
#define EnemyH 50
const double EnemyCD = 500;
class Enemy : public MovingObj
{
public :
    double HP;
    double CoolDown = EnemyCD;
public :
    Area RectOccupy = {0, 0, 0, 0};
    void SetOccupy();
    int CheckOccupy(std::list<Enemy>& enemies);
    void MoveOccupy(std::list<Enemy>& enemies);

public :
    Enemy();
    ~Enemy();
    void Chase();
    void SetUp(int x, int y, int type);
};
