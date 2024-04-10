#pragma once
#include "../../src/Object/TextObj/TextObj.hpp"
#include "../../asset/ImgTextLoad/ImgTextLoad.hpp"
class KillCount : public TextObj
{
private :
    int Count = 0;
public :
    KillCount();
    ~KillCount();

    void Add();
    void Display();
};
