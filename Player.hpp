#pragma once
#include "BasicFn.hpp"
#include "BigObj.hpp"
#include "Map.hpp"
#include "Enemy.hpp"
#include "Power.hpp"
#include <vector>
#define PlayerWidth 60
#define PlayerHeight 50

class Player : public BigObj
{
public :
    Player();
    ~Player();
private :
    int a_x = 0, a_y = 0;
    int v_Player = 7;
    int dir = 0;
    const char* PlayerImg = "player.jpg";
//public :
//    std::vector<Ammo*> AmmoList;
public :
    void ResetInput();
    void KeyInput();
    void Move( Map &BackGr, std::list<Enemy> &enemies, std::list<Power> &powers );
    void SetDir();
    int GetDir();
//    void SetAmmoList(std::vector<Ammo*> ammoList  );
//    std::vector<Ammo*> GetAmmoList();

};
