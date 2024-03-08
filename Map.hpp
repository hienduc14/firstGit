#pragma once
#include "BasicFn.hpp"
#include "BigObj.hpp"
#define MapWidth SCREEN_WIDTH
#define MapHeight SCREEN_HEIGHT
class Map : public BigObj
{
public :
    Map();
    ~Map();
private :
    const char* MapImg = "EndlessMap.png";
public :
    void MapMove( int u, int v );
};
