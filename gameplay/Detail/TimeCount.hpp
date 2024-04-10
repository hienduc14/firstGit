#pragma once
#include "../../src/Object/TextObj/TextObj.hpp"
#include "../../src/TimeManage/Time.hpp"
#include "../../asset/ImgTextLoad/ImgTextLoad.hpp"
class TimeCount : public TextObj
{
public :
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
