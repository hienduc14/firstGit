#pragma once
#include "TextObj.hpp"
#include "Time.hpp"
class TimeCount : public TextObj
{
private :
    double minute = 0, second = 0;
    std::string clock;
public :
    TimeCount();
    ~TimeCount();

    void UpdateTime();
    void Shorten();
    std::string TimeToStr();
    void Display();
};
