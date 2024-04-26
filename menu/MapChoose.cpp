#include "MapChoose.hpp"

MapChoose::MapChoose()
{
//    Screen BackGround;
    BackGround.rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    BackGround.texture = pre::BlurTexture;
    SDL_QueryTexture(BackGround.texture, NULL, NULL, &BackGround.rectst.w, &BackGround.rectst.h);

//    Button Option;)
    for( int i = 0; i < 3; i++ ) MapOption[i].texture = pre::MapOptionTexture[i];
    for( int i = 0; i < 3; i++ ){
        SDL_QueryTexture(MapOption[i].texture, NULL, NULL, &MapOption[i].rectst.w, &MapOption[i].rectst.h);
        MapOption[i].rect.w = MapOption[i].rectst.w;
        MapOption[i].rect.h = MapOption[i].rectst.h;
        MapOption[i].rect.x = CENTER_X - MapOption[i].rect.w/2 + (MapOption[i].rect.w + 30)*(i-1);
        MapOption[i].rect.y = CENTER_Y - MapOption[i].rect.h/2;
    }
}

MapChoose::~MapChoose()
{
}

void MapChoose::Draw()
{
    BackGround.drawObj();
    for( int i = 0; i < 3; i++ ) MapOption[i].drawObj();
}

int MapChoose::play()
{
    for( int i = 0; i < 3; i++ ) MapOption[i].CheckMouse(base::g_event);
    for( int i = 0; i < 3; i++ ) if( MapOption[i].status ){
//        std::cout << i << '\n';
        return i;
    }
    return -1;
}
