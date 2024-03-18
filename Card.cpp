#include "Card.hpp"

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
    content = func::random( 1, 3 );
    switch (content)
    {
    case 1:
        this->texture = pre::HPCardTexture;
        break;
    case 2:
        this->texture = pre::WaterBallCardTexture;
        break;
    case 3:
        this->texture = pre::FireBallCardTexture;
        break;
//    case 4:
//        this->texture = pre::HPCardTexture;
    }
}

void Card::Update( Player &player )
{
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
    }
    content = 0;
}
