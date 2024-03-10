#pragma once
#include "BasicFn.hpp"
#include "BigObj.hpp"
#include "Map.hpp"
#include "Enemy.hpp"
#include "Power.hpp"
#include <vector>
#define PlayerWidth 60
#define PlayerHeight 50
const std::string PlayerImg = "player.jpg";

class Player : public BigObj
{
public :
    Player();
    ~Player();
private :
    int a_x = 0, a_y = 0;
    int v_Player = 7;
    int dir = 0;
    bool MyPower[5] = {0, 0, 0, 0, 0};
    int Cycle[5] = {1, 0, 0, 0, 0};
public :
    int HP = 30;
public :
    void ResetInput();
    void KeyInput();
    void Move( Map &BackGr, std::list<Enemy> &enemies, std::list<Power> &powers );
    void SetDir();
    int GetDir();
    void SetPower( int x );
    int GetPower( int x );
    void SetCycle( int x, int t );
    int GetCycle( int t );
};
