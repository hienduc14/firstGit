#pragma once
#include "../../Function/BasicFn/BasicFn.hpp"
#include "../BigObj/BigObj.hpp"
class Screen : public BigObj
{
public :
    Screen();
    ~Screen();
public :

    int MapWidth;
    int MapHeight;
    void SetMap();
    void MapMove( double u, double v );
};
