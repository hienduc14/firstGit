#pragma once
#include "../src/Function/BasicFn/BasicFn.hpp"
#include "../src/Object/Screen/Screen.hpp"
#include "../src/Object/Button/Button.hpp"


class MapChoose
{
public :
    MapChoose();
    ~MapChoose();
private :
    Screen BackGround;
    Button Option[3];
public :
    void Draw();
    int play();
};

