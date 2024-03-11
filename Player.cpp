#include "Player.hpp"
Player::Player()
{
    this->rectst = {0, 0, PlayerWidth, PlayerHeight};
    this->rect.x = CENTER_X - PlayerWidth/2;
    this->rect.y = CENTER_Y - PlayerHeight/2;
    this->rect.w = PlayerWidth;
    this->rect.h = PlayerHeight;
    this->SetTexture(PlayerImg);
    this->dir = 1;
}

Player::~Player()
{

}

void Player::ResetInput(){ a_x = 0; a_y = 0; }

void Player::KeyInput()
{
    const Uint8* state = SDL_GetKeyboardState(nullptr);
    if( state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP] )       a_y -= v_Player;
    if( state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN] )     a_y += v_Player;
    if( state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT] )     a_x -= v_Player;
    if( state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT] )    a_x += v_Player;
}
void Player::SetDir(){
    if( a_x > 0 && a_y == 0 ) dir = 0;
    if( a_x > 0 && a_y > 0 ) dir = 1;
    if( a_x == 0 && a_y > 0 ) dir = 2;
    if( a_x < 0 && a_y > 0 ) dir = 3;
    if( a_x < 0 && a_y == 0 ) dir = 4;
    if( a_x < 0 && a_y < 0 ) dir = 5;
    if( a_x == 0 && a_y < 0 ) dir = 6;
    if( a_x > 0 && a_y < 0 ) dir = 7;
}

int Player::GetDir(){
    return this->dir;
}

void Player::Move( Screen &Map, std::list<Enemy> &enemies, std::list<Power> &powers, std::list<Exp> &exps )
{
    SetDir();
    Map.MapMove( -a_x, -a_y );
    for( auto &enemy : enemies ) enemy.Change( -a_x, -a_y );
    for( auto &exp : exps ) exp.Change( -a_x, -a_y );
    for( auto &power : powers ) power.Change( -a_x, -a_y );
}

void Player::SetPower( int x ){MyPower[x] = 1;}
int Player::GetPower( int x ){return MyPower[x];}
void Player::SetCycle( int x, int t ){ Cycle[t] = x; }
int Player::GetCycle( int t ){ return Cycle[t]; }
