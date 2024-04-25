#include "TimeCount.hpp"

TimeCount::TimeCount()
{

}

TimeCount::~TimeCount()
{

}

void TimeCount::UpdateTime()
{
    second += TimeManager::Instance()->getElapsedTime();
    Shorten();
    clock = TimeToStr();
}

void TimeCount::Shorten()
{
    int add = second/60;
    minute += add;
    second -= add*60;
}

std::string TimeCount::TimeToStr()
{
    int m = minute, s = second;
    std::string res;
    res = res + std::to_string(m);
    res = res + ":";
    if( s < 10 ) res = res + "0";
    res = res + std::to_string(int(second));
    return res;
}

void TimeCount::Display()
{
    SetTTF(clock, 0, 0, pre::CountFont, color);
    rect.x = CENTER_X - rect.w/2;
    drawObj();
}
