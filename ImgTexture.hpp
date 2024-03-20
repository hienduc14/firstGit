#pragma once
#include "BasicFn.hpp"

const std::string SlimeImg = "slime.png";
const std::string OrbImg = "orb.png";
const std::string FireBallImg = "FireBalls.png";
const std::string ZoneImg = "zone.png   ";
const std::string ExpImg = "exp.png";
const std::string PlayerImg = "PlayerSlime.png";
const std::string MapImg = "EndlessMap.png";
const std::string HealthImg = "hp.png";
const std::string HealthBarImg = "hp_bar.png";
const std::string ExpPointImg = "exp_point.png";
const std::string ExpBarImg = "exp_bar.png";
const std::string HPCardImg = "HPCard.png";
const std::string WaterBallCardImg = "WaterBallCard.png";
const std::string FireBallCardImg = "FireBallCard.png";
namespace pre
{
    extern SDL_Texture* MapTexture;
    extern SDL_Texture* SlimeTexture;
    extern SDL_Texture* OrbTexture;
    extern SDL_Texture* FireBallTexture;
    extern SDL_Texture* ZoneTexture;
    extern SDL_Texture* ExpTexture;
    extern SDL_Texture* PlayerTexture;
    extern SDL_Texture* HealthTexture;
    extern SDL_Texture* HealthBarTexture;
    extern SDL_Texture* ExpPointTexture;
    extern SDL_Texture* ExpBarTexture;
    extern SDL_Texture* HPCardTexture;
    extern SDL_Texture* WaterBallCardTexture;
    extern SDL_Texture* FireBallCardTexture;
    extern SDL_Texture* Option[5][5];
}

class LoadAll
{
public:
    LoadAll();
    ~LoadAll();
    void loading();
};
