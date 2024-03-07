#pragma once
#include "BasicFn.hpp"
#include "BigObj.hpp"

static int PlayerWidth = 150;
static int PlayerHeight = 100;
static std::string PlayerImg = "player.jpg";
class Player : public BigObj
{
public :
    Player();
    ~Player();
private :
    int a_x = 0, a_y = 0;
    int v_Player = 10;
public :
    void ResetInput();
    void KeyInput( SDL_Event Events );
    void Move();
};
