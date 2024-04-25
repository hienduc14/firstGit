#include "./ImgTextLoad.hpp"

namespace pre
{
    SDL_Texture* MapTexture = nullptr;

    SDL_Texture* SlimeTexture= nullptr;
    SDL_Texture* RabbitTexture= nullptr;
    SDL_Texture* BoarTexture= nullptr;

    int SlimeFrame = 0, RabbitFrame = 0, BoarFrame = 0;

    SDL_Texture* OrbTexture= nullptr;
    SDL_Texture* FireBallTexture= nullptr;
    SDL_Texture* ZoneTexture= nullptr;

    SDL_Texture* KamehaTexture= nullptr;
    SDL_Texture* AimArrowTexture= nullptr;
    SDL_Texture* BossKamehaTexture= nullptr;
    SDL_Texture* BossAimArrowTexture= nullptr;


    SDL_Texture* ExpTexture= nullptr;
    SDL_Texture* CoinTexture= nullptr;
    SDL_Texture* HeartTexture= nullptr;

    SDL_Texture* PlayerTexture= nullptr;
    SDL_Texture* HealthTexture= nullptr;
    SDL_Texture* HealthBarTexture= nullptr;
    SDL_Texture* ExpPointTexture= nullptr;
    SDL_Texture* ExpBarTexture= nullptr;
    SDL_Texture* HPCardTexture= nullptr;
    SDL_Texture* WaterBallCardTexture= nullptr;
    SDL_Texture* FireBallCardTexture= nullptr;
    SDL_Texture* Option[8][8];

    TTF_Font* DmgFont = nullptr;
    TTF_Font* CountFont = nullptr;
    SDL_Texture* SkullIcon = nullptr;
}

LoadAll::LoadAll(){}
LoadAll::~LoadAll(){}
void LoadAll::loading( int MapTerrain )
{
    switch (MapTerrain)
    {
        case 0 :
        {
            pre::MapTexture     = base::Load_Image(std::string("./asset/Map/Meadow.png"));
            pre::SlimeTexture   = base::Load_Image(std::string("./asset/Enemy/RedSlime.png"));
            pre::RabbitTexture  = base::Load_Image(std::string("./asset/Enemy/Rabbit.png"));
            pre::BoarTexture    = base::Load_Image(std::string("./asset/Enemy/Boar.png"));
            pre::SlimeFrame = 10;
            pre::RabbitFrame = 6;
            pre::BoarFrame = 6;
            break;
        }
        case 1 :
        {
            pre::MapTexture     = base::Load_Image(std::string("./asset/Map/GraveYard.png"));
            pre::SlimeTexture   = base::Load_Image(std::string("./asset/Enemy/Ghost.png"));
            pre::RabbitTexture  = base::Load_Image(std::string("./asset/Enemy/Bat.png"));
            pre::BoarTexture    = base::Load_Image(std::string("./asset/Enemy/Zombie.png"));
            pre::SlimeFrame = 10;
            pre::RabbitFrame = 6;
            pre::BoarFrame = 6;
            break;
        }
        case 2 :
        {
            pre::MapTexture     = base::Load_Image(std::string("./asset/Map/Volcano.png"));
            pre::SlimeTexture   = base::Load_Image(std::string("./asset/Enemy/FlameSlime.png"));
            pre::RabbitTexture  = base::Load_Image(std::string("./asset/Enemy/CoalMonster.png"));
            pre::BoarTexture    = base::Load_Image(std::string("./asset/Enemy/FireElement.png"));
            pre::SlimeFrame = 8;
            pre::RabbitFrame = 8;
            pre::BoarFrame = 8;
            break;
        }
    }
//    pre::SlimeTexture   = base::Load_Image(std::string("./asset/Enemy/RedSlime.png"));
//    pre::RabbitTexture  = base::Load_Image(std::string("./asset/Enemy/Rabbit.png"));
//    pre::BoarTexture    = base::Load_Image(std::string("./asset/Enemy/Boar.png"));

    pre::ExpTexture     = base::Load_Image(std::string("./asset/Enemy/Exp.png"));
    pre::CoinTexture     = base::Load_Image(std::string("./asset/Enemy/Coin.png"));
    pre::HeartTexture     = base::Load_Image(std::string("./asset/Enemy/Heart.png"));

    pre::OrbTexture         = base::Load_Image(std::string("./asset/Power/orb.png"));
    pre::FireBallTexture    = base::Load_Image(std::string("./asset/Power/FireBalls.png"));
    pre::ZoneTexture        = base::Load_Image(std::string("./asset/Power/zone.png"));

    pre::KamehaTexture      = base::Load_Image(std::string("./asset/Power/Kameha.png"));
    pre::AimArrowTexture      = base::Load_Image(std::string("./asset/Power/AimArrow.png"));
    pre::BossKamehaTexture      = base::Load_Image(std::string("./asset/Enemy/BossKameha.png"));
    pre::BossAimArrowTexture      = base::Load_Image(std::string("./asset/Enemy/BossAimArrow.png"));

    pre::PlayerTexture      = base::Load_Image(std::string("./asset/Player/PlayerSlime.png"));
    pre::HealthTexture      = base::Load_Image(std::string("./asset/Player/hp.png"));
    pre::HealthBarTexture   = base::Load_Image(std::string("./asset/Player/hp_bar.png"));
    pre::ExpPointTexture    = base::Load_Image(std::string("./asset/Player/exp_point.png"));
    pre::ExpBarTexture      = base::Load_Image(std::string("./asset/Player/exp_bar.png"));
    pre::Option[1][0] = base::Load_Image(std::string("./asset/Card/HPCard.png"));
    pre::Option[2][0] = base::Load_Image(std::string("./asset/Card/ExpCard.png"));
    pre::Option[3][0] = base::Load_Image(std::string("./asset/Card/DefenseCard.png"));
    pre::Option[4][0] = base::Load_Image(std::string("./asset/Card/WaterBallCard.png"));
    pre::Option[4][1] = base::Load_Image(std::string("./asset/Card/WaterBallCardLV2.png"));
    pre::Option[4][2] = base::Load_Image(std::string("./asset/Card/WaterBallCardLV3.png"));
    pre::Option[4][3] = base::Load_Image(std::string("./asset/Card/WaterBallCardLV4.png"));
    pre::Option[5][0] = base::Load_Image(std::string("./asset/Card/FireBallCard.png"));
    pre::Option[5][1] = base::Load_Image(std::string("./asset/Card/FireBallCardLV2.png"));
    pre::Option[5][2] = base::Load_Image(std::string("./asset/Card/FireBallCardLV3.png"));
    pre::Option[5][3] = base::Load_Image(std::string("./asset/Card/FireBallCardLV4.png"));
    pre::Option[6][0] = base::Load_Image(std::string("./asset/Card/ZoneCard.png"));
    pre::Option[6][1] = base::Load_Image(std::string("./asset/Card/ZoneCardLV2.png"));
    pre::Option[6][2] = base::Load_Image(std::string("./asset/Card/ZoneCardLV3.png"));
    pre::Option[6][3] = base::Load_Image(std::string("./asset/Card/ZoneCardLV4.png"));

    pre::DmgFont    = TTF_OpenFont("./asset/CountFont.ttf", 40);
    pre::CountFont  = TTF_OpenFont("./asset/CountFont.ttf", 70);
    pre::SkullIcon  = base::Load_Image(std::string("./asset/Screen/Skull.png"));
}
