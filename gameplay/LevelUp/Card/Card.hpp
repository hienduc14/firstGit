#pragma once
#include "../../Player/Player.hpp"
#include "../../Opponent/Enemy/Enemy.hpp"
#include "../../Opponent/Exp/Exp.hpp"
#include "../../../src/Object/Button/Button.hpp"
#include "../../../src/Function/Func/Func.hpp"
#include "../../../asset/ImgTextLoad/ImgTextLoad.hpp"
#define CardImgW 563
#define CardImgH 791
#define CardW 281
#define CardH 395
namespace pre
{
    extern int OptionUsed[7];
}
class Card : public Button
{
public :
    Card();
    ~Card();
public :
    int content = -1;
public :
    void Appear( int tt );
    void Random();
    void Update( Player &player );
};

