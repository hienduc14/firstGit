#pragma once
#include "TextObj.hpp"

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
