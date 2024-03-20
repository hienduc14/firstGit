#include "Card.hpp"

namespace pre
{
    int OptionUsed[5] = {0, 0, 0, 0, 0};
}

Card::Card()
{
    rectst = {0, 0, CardImgW, CardImgH};
    rect = {0, CENTER_Y-CardH/2, CardW, CardH};
}

Card::~Card()
{

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
        content = func::random( 1, 4 );
    }while( 2 <= content && content <= 4 && pre::OptionUsed[content]+1 > 4);
    this->texture = pre::Option[content][pre::OptionUsed[content]];
    return;
}

void Card::Update( Player &player )
{
    if( 2 <= content && content <= 4 ) pre::OptionUsed[content]++;
    switch (content)
    {
    case 1:
        player.HPMax = 1.2*player.HPMax;
        player.HP = 1.2*player.HP;
        break;
    case 2:
        //WaterBall
        player.SetPower( 0 );
        break;
    case 3:
        //FireBall
        player.SetPower( 1 );
        break;

    case 4:
        //zone
        player.SetPower( 2 );
        break;
    }
    content = 0;
}
