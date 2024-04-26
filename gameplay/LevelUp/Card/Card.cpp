#include "Card.hpp"

namespace pre
{
    int OptionUsed[7] = {0, 0, 0, 0, 0, 0, 0};
}

Card::Card()
{
    rectst = {0, 0, CardImgW, CardImgH};
    rect = {0, CENTER_Y-CardH/2, CardW, CardH};
}

Card::~Card()
{
    texture = nullptr;
}

void Card::Appear( int tt )
{
    status = 0; content = 0;
    rect.x = CENTER_X - CardW/2 + tt*(CardW + 10);
    Random();
}

void Card::Random()
{
    do{
        content = func::random( 1, 6 );
    }while( 4 <= content && content <= 6 && pre::OptionUsed[content] > 3 );
    this->texture = pre::Option[content][pre::OptionUsed[content]];

    if( texture == nullptr ){
        std::cout << content << " " << pre::OptionUsed[content] << '\n';

    }
    return;
}

void Card::Update( Player &player )
{
    if( 4 <= content && content <= 6 ) pre::OptionUsed[content]++;
    switch (content)
    {
    case 1:
        player.HPMax = 1.2*player.HPMax;
        player.HP = 1.2*player.HP;
        break;
    case 2:
        player.Defense *= 0.9;
        break;
    case 3:
        player.ExpGain *= 1.1;
        break;
    case 4:
        //WaterBall
        player.MyPower[0]++;
//        player.SetPower( 0 );
        break;
    case 5:
        //FireBall
        player.MyPower[1]++;
        break;
    case 6:
        //zone
        player.MyPower[2]++;
        break;
    }
}
