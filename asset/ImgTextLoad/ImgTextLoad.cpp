#include "./ImgTextLoad.hpp"

namespace pre
{
    SDL_Texture* Opponent[4][3];
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

    Mix_Chunk* KamehaSound = nullptr;
    Mix_Chunk* JumpSound = nullptr;

    SDL_Texture* MainMenuTexture = nullptr;
    SDL_Texture* PlayTexture = nullptr;
    SDL_Texture* ShopTexture = nullptr;
    SDL_Texture* TutorialTexture = nullptr;
    SDL_Texture* OptionsTexture = nullptr;
    SDL_Texture* BlurTexture = nullptr;
    SDL_Texture* BackTexture = nullptr;
    SDL_Texture* ExitMenuTexture = nullptr;
    SDL_Texture* ExitTexture = nullptr;
    SDL_Texture* TickBoxTexture = nullptr;
    SDL_Texture* SoundEFVoloumeTexture = nullptr;
    SDL_Texture* SoundEFPointTexture = nullptr;
    SDL_Texture* MusicVoloumeTexture = nullptr;
    SDL_Texture* MusicPointTexture = nullptr;
    SDL_Texture* ShopMenuTexture = nullptr;
    SDL_Texture* SkinTexture[4];
    SDL_Texture* SkinBoughtTexture[4];
    SDL_Texture* BuyTexture;
    SDL_Texture* UsedTexture = nullptr;
    SDL_Texture* TutorialMenuTexture = nullptr;
    SDL_Texture* MapOptionTexture[3];
    SDL_Texture* PauseMenu = nullptr;
    SDL_Texture* Pause = nullptr;
    SDL_Texture* Resume = nullptr;
    SDL_Texture* Home = nullptr;

    SDL_Texture* PlayerSlime[4];
    SDL_Texture* BossTexture[3];
}

LoadAll::LoadAll(){}
LoadAll::~LoadAll(){}
void LoadAll::loading()
{
    pre::Opponent[0][0]  = base::Load_Image(std::string("./asset/Map/Meadow.png"));
    pre::Opponent[0][1]  = base::Load_Image(std::string("./asset/Map/GraveYard.png"));
    pre::Opponent[0][2]  = base::Load_Image(std::string("./asset/Map/Volcano.png"));
    pre::Opponent[1][0]  = base::Load_Image(std::string("./asset/Enemy/RedSlime.png"));
    pre::Opponent[1][1]  = base::Load_Image(std::string("./asset/Enemy/Ghost.png"));
    pre::Opponent[1][2]  = base::Load_Image(std::string("./asset/Enemy/FlameSlime.png"));
    pre::Opponent[2][0]  = base::Load_Image(std::string("./asset/Enemy/Rabbit.png"));
    pre::Opponent[2][1]  = base::Load_Image(std::string("./asset/Enemy/Bat.png"));
    pre::Opponent[2][2]  = base::Load_Image(std::string("./asset/Enemy/FireElement.png"));
    pre::Opponent[3][0]  = base::Load_Image(std::string("./asset/Enemy/Boar.png"));
    pre::Opponent[3][1]  = base::Load_Image(std::string("./asset/Enemy/Zombie.png"));
    pre::Opponent[3][2]  = base::Load_Image(std::string("./asset/Enemy/CoalMonster.png"));
    pre::BossTexture[0] = base::Load_Image(std::string("./asset/Enemy/SlimeBoss.png"));
    pre::BossTexture[1] = base::Load_Image(std::string("./asset/Enemy/GhostBoss.png"));
    pre::BossTexture[2] = base::Load_Image(std::string("./asset/Enemy/FlameBoss.png"));
//    switch (MapTerrain)
//    {
//        case 0 :
//        {
//            pre::MapTexture     = base::Load_Image(std::string("./asset/Map/Meadow.png"));
//            pre::SlimeTexture   = base::Load_Image(std::string("./asset/Enemy/RedSlime.png"));
//            pre::RabbitTexture  = base::Load_Image(std::string("./asset/Enemy/Rabbit.png"));
//            pre::BoarTexture    = base::Load_Image(std::string("./asset/Enemy/Boar.png"));
//            pre::SlimeFrame = 10;
//            pre::RabbitFrame = 6;
//            pre::BoarFrame = 6;
//            break;
//        }
//        case 1 :
//        {
//            pre::MapTexture     = base::Load_Image(std::string("./asset/Map/GraveYard.png"));
//            pre::SlimeTexture   = base::Load_Image(std::string("./asset/Enemy/Ghost.png"));
//            pre::RabbitTexture  = base::Load_Image(std::string("./asset/Enemy/Bat.png"));
//            pre::BoarTexture    = base::Load_Image(std::string("./asset/Enemy/Zombie.png"));
//            pre::SlimeFrame = 10;
//            pre::RabbitFrame = 6;
//            pre::BoarFrame = 6;
//            break;
//        }
//        case 2 :
//        {
//            pre::MapTexture     = base::Load_Image(std::string("./asset/Map/Volcano.png"));
//            pre::SlimeTexture   = base::Load_Image(std::string("./asset/Enemy/FlameSlime.png"));
//            pre::RabbitTexture  = base::Load_Image(std::string("./asset/Enemy/CoalMonster.png"));
//            pre::BoarTexture    = base::Load_Image(std::string("./asset/Enemy/FireElement.png"));
//            pre::SlimeFrame = 8;
//            pre::RabbitFrame = 8;
//            pre::BoarFrame = 8;
//            break;
//        }
////    }
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

    if( pre::DmgFont == nullptr ) pre::DmgFont    = TTF_OpenFont("./asset/CountFont.ttf", 40);
    if( pre::CountFont == nullptr ) pre::CountFont  = TTF_OpenFont("./asset/CountFont.ttf", 70);
    if( pre::SkullIcon == nullptr ) pre::SkullIcon  = base::Load_Image(std::string("./asset/Screen/Skull.png"));

    if( pre::KamehaSound == nullptr ) pre::KamehaSound = Mix_LoadWAV("./asset/Sound/KamehaSound.WAV");
    if( pre::JumpSound == nullptr ) pre::JumpSound = Mix_LoadWAV("./asset/Sound/JumpSound.WAV");

    pre::MainMenuTexture = base::Load_Image(std::string("./menu/Menu.png"));
    pre::PlayTexture = base::Load_Image(std::string("./menu/play.png"));
    pre::ShopTexture = base::Load_Image(std::string("./menu/Shop.png"));
    pre::TutorialTexture = base::Load_Image(std::string("./menu/Tutorial.png"));
    pre::OptionsTexture = base::Load_Image(std::string("./menu/Options.png"));
    pre::BlurTexture = base::Load_Image(std::string("./menu/Blur.png"));
    pre::BackTexture = base::Load_Image(std::string("./menu/Back.png"));
    pre::ExitMenuTexture = base::Load_Image(std::string("./menu/ExitMenu.png"));
    pre::ExitTexture = base::Load_Image(std::string("./menu/Exit.png"));
    pre::TickBoxTexture = base::Load_Image(std::string("./menu/TickBox.png"));
    pre::SoundEFVoloumeTexture = base::Load_Image(std::string("./menu/Volume.png"));
    pre::SoundEFPointTexture = base::Load_Image(std::string("./menu/VolumePoint.png"));
    pre::MusicVoloumeTexture = base::Load_Image(std::string("./menu/Volume.png"));
    pre::MusicPointTexture = base::Load_Image(std::string("./menu/VolumePoint.png"));
    pre::ShopMenuTexture = base::Load_Image(std::string("./menu/Shop/ShopMenu.png"));
    pre::SkinTexture[0] = base::Load_Image(std::string("./menu/Shop/Skin0Bought.png"));
    pre::SkinTexture[1] = base::Load_Image(std::string("./menu/Shop/Skin1Bought.png"));
    pre::SkinBoughtTexture[0] = base::Load_Image(std::string("./menu/Shop/Skin0Bought.png"));
    pre::SkinBoughtTexture[1] = base::Load_Image(std::string("./menu/Shop/Skin1Bought.png"));
    pre::BuyTexture = base::Load_Image(std::string("./menu/Shop/Buy.png"));;
    pre::UsedTexture = base::Load_Image(std::string("./menu/Shop/Used.png"));
    pre::TutorialMenuTexture = base::Load_Image(std::string("./menu/TutorialMenu.png"));

    pre::MapOptionTexture[0] = base::Load_Image(std::string("./menu/MeadowOption.png"));
    pre::MapOptionTexture[1] = base::Load_Image(std::string("./menu/GraveyardOption.png"));
    pre::MapOptionTexture[2] = base::Load_Image(std::string("./menu/VolcanoOption.png"));

    pre::PauseMenu = base::Load_Image(std::string("./menu/PauseMenu.png"));
    pre::Pause = base::Load_Image(std::string("./menu/Pause.png"));
    pre::Resume = base::Load_Image(std::string("./menu/Resume.png"));
    pre::Home = base::Load_Image(std::string("./menu/Home.png"));

    pre::PlayerSlime[0] = base::Load_Image(std::string("./asset/Player/Slime0.png"));
    pre::PlayerSlime[1] = base::Load_Image(std::string("./asset/Player/Slime1.png"));
}


void LoadAll::release()
{
    SDL_DestroyTexture( pre::MapTexture );
    pre::MapTexture = nullptr;

    SDL_DestroyTexture( pre::SlimeTexture);
    pre::SlimeTexture= nullptr;
    SDL_DestroyTexture( pre::RabbitTexture);
    pre::RabbitTexture = nullptr;
    SDL_DestroyTexture( pre::BoarTexture );
    pre::BoarTexture = nullptr;

    int SlimeFrame = 0, RabbitFrame = 0, BoarFrame = 0;

    SDL_DestroyTexture( pre::OrbTexture ); pre::OrbTexture = nullptr;
    SDL_DestroyTexture( pre::FireBallTexture ); pre::FireBallTexture = nullptr;
    SDL_DestroyTexture( pre::ZoneTexture ); pre::ZoneTexture = nullptr;

    SDL_DestroyTexture( pre::KamehaTexture ); pre::KamehaTexture = nullptr;
    SDL_DestroyTexture( pre::AimArrowTexture ); pre::AimArrowTexture = nullptr;
    SDL_DestroyTexture( pre::BossKamehaTexture ); pre::BossKamehaTexture = nullptr;
    SDL_DestroyTexture( pre::BossAimArrowTexture ); pre::BossAimArrowTexture = nullptr;

    SDL_DestroyTexture( pre::ExpTexture ); pre::ExpTexture = nullptr;
    SDL_DestroyTexture( pre::CoinTexture ); pre::CoinTexture = nullptr;
    SDL_DestroyTexture( pre::HeartTexture ); pre::HeartTexture = nullptr;

    SDL_DestroyTexture( pre::PlayerTexture ); pre::PlayerTexture = nullptr;
    SDL_DestroyTexture( pre::HealthTexture ); pre::HealthTexture = nullptr;
    SDL_DestroyTexture( pre::HealthBarTexture ); pre::HealthBarTexture = nullptr;
    SDL_DestroyTexture( pre::ExpPointTexture ); pre::ExpPointTexture = nullptr;
    SDL_DestroyTexture( pre::ExpBarTexture ); pre::ExpBarTexture = nullptr;

    SDL_DestroyTexture( pre::HPCardTexture ); pre::HPCardTexture = nullptr;
    SDL_DestroyTexture( pre::WaterBallCardTexture ); pre::WaterBallCardTexture = nullptr;
    SDL_DestroyTexture( pre::FireBallCardTexture ); pre::FireBallCardTexture = nullptr;

    for( int i = 0; i <= 7; i++ )
        for( int j = 0; j <= 7; j++ )
        {
            SDL_DestroyTexture( pre::Option[i][j] );
            pre::Option[i][j] = nullptr;
        }

}
