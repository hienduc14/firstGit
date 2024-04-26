#pragma once
#include "../../src/Function/BasicFn/BasicFn.hpp"

namespace pre
{
    extern SDL_Texture* Opponent[4][3];

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

    extern SDL_Texture* MainMenuTexture;
    extern SDL_Texture* PlayTexture;
    extern SDL_Texture* ShopTexture;
    extern SDL_Texture* TutorialTexture;
    extern SDL_Texture* OptionsTexture;
    extern SDL_Texture* BlurTexture;
    extern SDL_Texture* BackTexture;
    extern SDL_Texture* ExitMenuTexture;
    extern SDL_Texture* ExitTexture;
    extern SDL_Texture* TickBoxTexture;
    extern SDL_Texture* SoundEFVoloumeTexture;
    extern SDL_Texture* SoundEFPointTexture;
    extern SDL_Texture* MusicVoloumeTexture;
    extern SDL_Texture* MusicPointTexture;
    extern SDL_Texture* ShopMenuTexture;
    extern SDL_Texture* SkinTexture[4];
    extern SDL_Texture* SkinBoughtTexture[4];
    extern SDL_Texture* BuyTexture;
    extern SDL_Texture* UsedTexture;
    extern SDL_Texture* TutorialMenuTexture;
    extern SDL_Texture* MapOptionTexture[3];
    extern SDL_Texture* PauseMenu;
    extern SDL_Texture* Pause;
    extern SDL_Texture* Resume;
    extern SDL_Texture* Home;
    extern SDL_Texture* PlayerSlime[4];
    extern SDL_Texture* BossTexture[3];
}

class LoadAll
{
public:
    LoadAll();
    ~LoadAll();
    void loading();
    void release();
};
