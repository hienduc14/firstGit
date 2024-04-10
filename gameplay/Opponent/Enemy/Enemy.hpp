#pragma once
#include "../../../src/Object/MovingObj/MovingObj.hpp"
#include "../../../src/Function/Func/Func.hpp"
#include "../../../asset/ImgTextLoad/ImgTextLoad.hpp"
#define EnemyW 50
#define EnemyH 50
const double EnemyCD = 500;

class Enemy : public MovingObj
{
public :
    double HP;
    double CoolDown = EnemyCD;
    int IsDot = 0;
public :
    Area RectOccupy = {0, 0, 0, 0};
    void SetOccupy();
    int CheckOccupy(std::list<Enemy>& enemies);
    void MoveOccupy(std::list<Enemy>& enemies);
    void ChangeOccupy(double ax, double ay, std::list<Enemy>& enemies);

public :
    Enemy();
    ~Enemy();
    void Chase();
    void SetUp(int x, int y, int type);
    void SetClip(double x, int y, bool IsClipSet);
};
