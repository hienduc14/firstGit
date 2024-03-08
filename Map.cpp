#include "Map.hpp"

Map::Map()
{
    this->rectst = {0, 0, MapWidth*3, MapHeight*3};
    this->rect = {-MapWidth, -MapHeight, MapWidth*3, MapHeight*3};
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
