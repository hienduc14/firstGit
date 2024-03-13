#pragma once
#include "BasicFn.hpp"
#include "BigObj.hpp"
#define MapWidth 1000
#define MapHeight 1000
const std::string MapImg = "EndlessMap.png";
class Screen : public BigObj
{
public :
    Screen();
    ~Screen();
public :
    void MapMove( double u, double v );
};
