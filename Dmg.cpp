#include "Dmg.hpp"

Dmg::Dmg()
{

}

Dmg::Dmg(double num, int x, int y)
{
    SetUp(NumToStr(num), x, y);
}

Dmg::~Dmg()
{

}

std::string Dmg::NumToStr(double num)
{
    int u = num;
    return std::to_string(u);
}

void Dmg::SetUp(std::string tex, int x, int y)
{
    texture = base::Load_Text(tex, pre::DmgFont, White);
    Border = base::Load_Text(tex, pre::DmgFont, Black);
    SDL_QueryTexture(texture, NULL, NULL, &rectst.w, &rectst.h);
    rectst.x = rectst.y = 0;
    rect.x = x; rect.y = y;
    rect.w = rectst.w; rect.h = rectst.h;
    SetClip();
}

void Dmg::SetClip()
{
    for(int i = 0; i < FadeIn; i++){
        clip[i].w = rectst.w*i/FadeIn;
        clip[i].h = rectst.h*i/FadeIn;
        clip[i].x = rect.x + (rect.w-clip[i].w)/2;
        clip[i].y = rect.y + (rect.h-clip[i].h)/2;
    }
    for(int i = 0; i < Stay; i++)
        clip[FadeIn+i] = rect;
    for(int i = 0; i < FadeOut; i++){
        int u = FrameNum-i-1;
        clip[u].w = rectst.w*i/FadeIn;
        clip[u].h = rectst.h*i/FadeIn;
        clip[u].x = rect.x + (rect.w-clip[u].w)/2;
        clip[u].y = rect.y + (rect.h-clip[u].h)/2;
    }
}
void Dmg::PopUp()
{
    CurrentTime += TimeManager::Instance()->getElapsedTime();
    if( CurrentTime >= FrameTime*FrameNum )
    {
        exist = 0;
        return;
    }
    int index = CurrentTime/FrameTime;
    Write(clip[index], true);
    return;
}

void Dmg::Write( SDL_Rect texrect, bool IsBorder )
{
    if( IsBorder == false ) SDL_RenderCopy(base::renderer, texture, &rectst, &texrect);
    else
    {
        SDL_RenderCopy(base::renderer, Border, &rectst, &texrect);
        texrect.x += 3; texrect.w -= 6;
        texrect.y += 3; texrect.h -= 6;
        SDL_RenderCopy(base::renderer, texture, &rectst, &texrect);
    }
}
