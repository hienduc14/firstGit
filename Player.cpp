#include "Player.hpp"

Player::Player()
{
    this->rect.x = SCREEN_WIDTH/2 - PlayerWidth/2;
    this->rect.y = SCREEN_HEIGHT/2 - PlayerHeight/2;
    this->rect.w = PlayerWidth;
    this->rect.h = PlayerHeight;
    this->SetTexture(PlayerImg);
}

Player::~Player()
{

}

void Player::ResetInput(){ a_x = 0; a_y = 0; }

void Player::KeyInput( SDL_Event Events )
{
    if(Events.type == SDL_KEYDOWN)
    {
        switch (Events.key.keysym.sym){
        case SDLK_UP:       a_y -= v_Player; break;
        case SDLK_DOWN:     a_y += v_Player; break;
        case SDLK_LEFT:     a_x -= v_Player; break;
        case SDLK_RIGHT:    a_x += v_Player; break;
        }
    }
//    else if(Events.type == SDL_KEYUP)
//    {
//        switch (Events.key.keysym.sym){
//        case SDLK_UP:       a_y += v_Player; break;
//        case SDLK_DOWN:     a_y -= v_Player; break;
//        case SDLK_LEFT:     a_x += v_Player; break;
//        case SDLK_RIGHT:    a_x -= v_Player; break;
//        }
//    }
}

void Player::Move( Map &BackGr )
{
//    this->rect.x += this->a_x;
//    if( rect.x < 0 || rect.x + rect.w > SCREEN_WIDTH )
//        rect.x -= a_x;
//    this->rect.y += this->a_y;
//    if( rect.y < 0 || rect.y + rect.h > SCREEN_HEIGHT )
//        rect.y -= a_y;
    BackGr.MapMove( -a_x, -a_y );
}
