#include "MapChoose.hpp"

MapChoose::MapChoose()
{
//    Screen BackGround;
    BackGround.rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    BackGround.SetTexture(std::string("./menu/Blur.png"));
    SDL_QueryTexture(BackGround.texture, NULL, NULL, &BackGround.rectst.w, &BackGround.rectst.h);

//    Button Option;
    Option[0].SetTexture(std::string("./menu/MeadowOption.png"));
    Option[1].SetTexture(std::string("./menu/GraveyardOption.png"));
    Option[2].SetTexture(std::string("./menu/VolcanoOption.png"));
    for( int i = 0; i < 3; i++ ){
        SDL_QueryTexture(Option[i].texture, NULL, NULL, &Option[i].rectst.w, &Option[i].rectst.h);
        Option[i].rect.w = Option[i].rectst.w;        Option[i].rect.h = Option[i].rectst.h;
        Option[i].rect.x = CENTER_X - Option[i].rect.w/2 + (Option[i].rect.w + 30)*(i-1);
        Option[i].rect.y = CENTER_Y - Option[i].rect.h/2;
    }
}

MapChoose::~MapChoose()
{

}

void MapChoose::Draw()
{
    BackGround.drawObj();
    for( int i = 0; i < 3; i++ ) Option[i].drawObj();
}

int MapChoose::play()
{
    for( int i = 0; i < 3; i++ ) Option[i].CheckMouse(base::g_event);
    for( int i = 0; i < 3; i++ ) if( Option[i].status ) return i;
    return -1;
}
