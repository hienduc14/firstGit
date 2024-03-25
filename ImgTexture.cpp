#include "ImgTexture.hpp"

namespace pre
{
    SDL_Texture* MapTexture = nullptr;
    SDL_Texture* SlimeTexture= nullptr;
    SDL_Texture* OrbTexture= nullptr;
    SDL_Texture* FireBallTexture= nullptr;
    SDL_Texture* ZoneTexture= nullptr;
    SDL_Texture* ExpTexture= nullptr;
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
void LoadAll::loading()
{
    pre::MapTexture = base::Load_Image(MapImg);
    pre::SlimeTexture = base::Load_Image(SlimeImg);
    pre::OrbTexture = base::Load_Image(OrbImg);
    pre::FireBallTexture = base::Load_Image(FireBallImg);
    pre::ZoneTexture = base::Load_Image(ZoneImg);
    pre::ExpTexture = base::Load_Image(ExpImg);
    pre::PlayerTexture = base::Load_Image(PlayerImg);
    pre::HealthTexture = base::Load_Image(HealthImg);
    pre::HealthBarTexture = base::Load_Image(HealthBarImg);
    pre::ExpPointTexture = base::Load_Image(ExpPointImg);
    pre::ExpBarTexture = base::Load_Image(ExpBarImg);
    pre::Option[1][0] = base::Load_Image(std::string("HPCard.png"));
    pre::Option[2][0] = base::Load_Image(std::string("ExpCard.png"));
    pre::Option[3][0] = base::Load_Image(std::string("DefenseCard.png"));
    pre::Option[4][0] = base::Load_Image(std::string("WaterBallCard.png"));
    pre::Option[4][1] = base::Load_Image(std::string("WaterBallCardLV2.png"));
    pre::Option[4][2] = base::Load_Image(std::string("WaterBallCardLV3.png"));
    pre::Option[4][3] = base::Load_Image(std::string("WaterBallCardLV4.png"));
    pre::Option[5][0] = base::Load_Image(std::string("FireBallCard.png"));
    pre::Option[5][1] = base::Load_Image(std::string("FireBallCardLV2.png"));
    pre::Option[5][2] = base::Load_Image(std::string("FireBallCardLV3.png"));
    pre::Option[5][3] = base::Load_Image(std::string("FireBallCardLV4.png"));
    pre::Option[6][0] = base::Load_Image(std::string("ZoneCard.png"));
    pre::Option[6][1] = base::Load_Image(std::string("ZoneCardLV2.png"));
    pre::Option[6][2] = base::Load_Image(std::string("ZoneCardLV3.png"));
    pre::Option[6][3] = base::Load_Image(std::string("ZoneCardLV4.png"));

    pre::DmgFont = TTF_OpenFont("CountFont.ttf", 40);
    pre::CountFont = TTF_OpenFont("CountFont.ttf", 70);
    pre::SkullIcon = base::Load_Image(std::string("Skull.png"));
}
