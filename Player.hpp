#pragma once
#include "BasicFn.hpp"
#include "BigObj.hpp"
#include "Map.hpp"
#include "Enemy.hpp"
#include <vector>
#define PlayerWidth 150
#define PlayerHeight 100

class Player : public BigObj
{
public :
    Player();
    ~Player();
private :
    int a_x = 0, a_y = 0;
    int v_Player = 5;
    int dir;
    const char* PlayerImg = "player.jpg";
//public :
//    std::vector<Ammo*> AmmoList;
public :
    void ResetInput();
    void KeyInput();
    void Move( Map &BackGr, Enemy &enemy );
    void SetDir();
    int GetDir();
//    void SetAmmoList(std::vector<Ammo*> ammoList  );
//    std::vector<Ammo*> GetAmmoList();

};
