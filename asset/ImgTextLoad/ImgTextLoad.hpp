#pragma once
#include "../../src/Function/BasicFn/BasicFn.hpp"

namespace pre
{
    extern SDL_Texture* MapTexture;

    extern SDL_Texture* SlimeTexture;
    extern SDL_Texture* RabbitTexture;
    extern SDL_Texture* BoarTexture;
    extern int SlimeFrame, RabbitFrame, BoarFrame;

    extern SDL_Texture* OrbTexture;
    extern SDL_Texture* FireBallTexture;
    extern SDL_Texture* ZoneTexture;

    extern SDL_Texture* KamehaTexture;
    extern SDL_Texture* AimArrowTexture;
    extern SDL_Texture* BossKamehaTexture;
    extern SDL_Texture* BossAimArrowTexture;

    extern SDL_Texture* ExpTexture;
    extern SDL_Texture* CoinTexture;
    extern SDL_Texture* HeartTexture;

    extern SDL_Texture* PlayerTexture;
    extern SDL_Texture* HealthTexture;
    extern SDL_Texture* HealthBarTexture;
    extern SDL_Texture* ExpPointTexture;
    extern SDL_Texture* ExpBarTexture;
    extern SDL_Texture* HPCardTexture;
    extern SDL_Texture* WaterBallCardTexture;
    extern SDL_Texture* FireBallCardTexture;
    extern SDL_Texture* Option[8][8];

    extern TTF_Font* DmgFont;
    extern TTF_Font* CountFont;
    extern SDL_Texture* SkullIcon;

    extern Mix_Chunk* KamehaSound;
    extern Mix_Chunk* JumpSound;

}

class LoadAll
{
public:
    LoadAll();
    ~LoadAll();
    void loading( int MapTerrain );
};
