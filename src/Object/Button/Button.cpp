#include "Button.hpp"

Button::Button()
{
    status = 0;
}
Button::~Button()
{

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

