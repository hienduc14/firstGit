#pragma once
#include "Player.hpp"
#include "Button.hpp"
#include "Func.hpp"
#include "ImgTexture.hpp"
#define CardImgW 563
#define CardImgH 791
#define CardW 281
#define CardH 395
//const SDL_Texture* OrbCard = base::Load_Image("");
//const SDL_Texture* FireBallCard = base::Load_Image("");
//const SDL_Texture* ZoneCard = base::Load_Image("");
namespace pre
{
    extern int OptionUsed[5];
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

