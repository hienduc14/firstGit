#pragma once
#include "BasicFn.hpp"
#include "BigObj.hpp"
#define MapWidth SCREEN_WIDTH
#define MapHeight SCREEN_HEIGHT
const std::string MapImg = "EndlessMap.png";
class Screen : public BigObj
{
public :
    Screen();
    ~Screen();
public :
    void MapMove( int u, int v );
};
