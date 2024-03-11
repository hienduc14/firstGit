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
//    if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONUP || e.type == SDL_MOUSEBUTTONDOWN ){
        int x, y;
        SDL_GetMouseState( &x, &y );
        if( rect.x <= x && rect.x+rect.w >= x && rect.y <= y && rect.y+rect.h >= y ){
            SDL_PollEvent( &e );
            switch (e.type){
				case SDL_MOUSEBUTTONDOWN:
				status = 1;
				break;

				case SDL_MOUSEBUTTONUP:
				status = 0;
				break;
            }
        }
        else status = 0;
//    }
}
