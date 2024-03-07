#include "Map.hpp"

Map::Map()
{
    this->rect.x = -MapWidth;
    this->rect.y = -MapHeight;
    this->rect.w = MapWidth*3;
    this->rect.h = MapHeight*3;
    this->SetTexture(MapImg);
}

Map::~Map()
{

}

void Map::MapMove(int u, int v){
    this->rect.x += u; this->rect.y += v;
    if( this->rect.x >= 0 ) this->rect.x-=SCREEN_WIDTH;
    if( this->rect.y >= 0 ) this->rect.y-=SCREEN_HEIGHT;
    if( this->rect.x <= -SCREEN_WIDTH*2 ) this->rect.x+=SCREEN_WIDTH;
    if( this->rect.y <= -SCREEN_HEIGHT*2 ) this->rect.y+=SCREEN_HEIGHT;
}
