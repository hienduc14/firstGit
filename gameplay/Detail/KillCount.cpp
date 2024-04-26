#include "KillCount.hpp"

KillCount::KillCount()
{

}

KillCount::~KillCount()
{

}

void KillCount::Add()
{
    Count++;
}

void KillCount::Display()
{
    SetTTF(std::to_string(Count), 10, 0, pre::CountFont, color);
    drawObj();
    SDL_Rect ST, EN;
    ST = {0, 0, 16, 15};
    EN.w = 40; EN.h = 40;
    EN.x = rect.x + rect.w + 10;
    EN.y = 25;
    SDL_RenderCopy(base::renderer, pre::SkullIcon,&ST, &EN );
}
