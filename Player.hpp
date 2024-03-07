#pragma once
#include "BasicFn.hpp"
#include "BigObj.hpp"
#include "Map.hpp"

class Player : public BigObj
{
public :
    Player();
    ~Player();
private :
    int a_x = 0, a_y = 0;
    int v_Player = 5;
    const int PlayerWidth = 150;
    const int PlayerHeight = 100;
    std::string PlayerImg = "player.jpg";
public :
    void ResetInput();
    void KeyInput( SDL_Event Events );
    void Move( Map &BackGr );
};
