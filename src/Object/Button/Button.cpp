#include "Button.hpp"

Button::Button()
{
    status = 0;
}
Button::~Button()
{
    texture = nullptr;
//    SDL_DestroyTexture(texture);
}

void Button::QuerySetup()
{
    SDL_QueryTexture(texture, nullptr, nullptr, &rectst.w, &rectst.h);
}

void Button::CheckMouse(SDL_Event &e)
{
    int x, y;
    this->status = 0;
    SDL_GetMouseState( &x, &y );
    if( rect.x <= x && rect.x+rect.w >= x && rect.y <= y && rect.y+rect.h >= y ){
        switch (e.type){
            case SDL_MOUSEBUTTONDOWN:
            {
                status = 1;
                break;
            }

            case SDL_MOUSEBUTTONUP:
            {
                status = 0;
                break;
            }
        }
    }
}

void Button::CheckTick(SDL_Event &e)
{
    int x, y;
    SDL_GetMouseState( &x, &y );
    if( rect.x <= x && rect.x+rect.w >= x && rect.y <= y && rect.y+rect.h >= y ){
        switch (e.type){
            case SDL_MOUSEBUTTONDOWN:
            {
                status = 1-status;
                break;
            }
        }
    }
}

void Button::drawTick()
{
    if( status == 0 ) drawObj();
}

void Button::CheckHold(SDL_Event &e)
{
    int x, y;
    SDL_GetMouseState( &x, &y );

    if( status == 1 )
    {
        int u = x-luu_x;
        if( rect.x + u >= limit.x && rect.x + u <= limit.x + limit.w )
            rect.x += u;
    }
    luu_x = x; luu_y = y;

    if( rect.x <= x && rect.x+rect.w >= x && rect.y <= y && rect.y+rect.h >= y ){
        switch (e.type){
            case SDL_MOUSEBUTTONDOWN:
            {
                status = 1;
                luu_x = x; luu_y = y;
//                std::cout << "YES-----------------\n";
                break;
            }
        }
    }
    if(e.type == SDL_MOUSEBUTTONUP ) status = 0;
}

void Button::drawHold()
{
    drawObj();
}

void Button::CheckChoice(SDL_Event &e, int &NeedChange, int Changed)
{
    if(CanPress == 0) return;
    int x, y;
    SDL_GetMouseState( &x, &y );
    if( rect.x <= x && rect.x+rect.w >= x && rect.y <= y && rect.y+rect.h >= y ){
        switch (e.type){
            case SDL_MOUSEBUTTONDOWN:
            {
                NeedChange = Changed;
                break;
            }
        }
    }
}

void Button::drawChoice()
{
    drawObj();
}
