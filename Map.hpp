#pragma once
#include "BasicFn.hpp"
#include "BigObj.hpp"

class Map : public BigObj
{
public :
    Map();
    ~Map();
private :
    int x, y;
    const int MapWidth = SCREEN_WIDTH;
    const int MapHeight = SCREEN_HEIGHT;
    std::string MapImg = "EndlessMap.png";
public :
    void MapMove( int u, int v );
};
