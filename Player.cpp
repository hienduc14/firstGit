#include "Player.hpp"
Player::Player()
{

}

Player::~Player()
{

}

void Player::SetUp()
{
    this->rectst = {0, 0, PlayerWidth, PlayerHeight};
    this->rect.x = CENTER_X - 25;
    this->rect.y = CENTER_Y - 18;
    this->rect.w = 50;
    this->rect.h = 36;
    this->texture = pre::PlayerTexture;
//    this->SetTexture(PlayerImg);
    this->dir = 1;
    SetHealthBar();
}

void Player::ResetInput(){ a_x = 0; a_y = 0; }

void Player::KeyInput()
{
    const Uint8* state = SDL_GetKeyboardState(nullptr);
    if( state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP] )       a_y -= v_Player*GameSpeed;
    if( state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN] )     a_y += v_Player*GameSpeed;
    if( state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT] )     a_x -= v_Player*GameSpeed;
    if( state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT] )    a_x += v_Player*GameSpeed;
    if( a_x && a_y ) a_x/=1.414, a_y/=1.414;
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

void Player::Move( Screen &Map, std::list<Enemy> &enemies, std::list<Orb> &orbs, std::list<FireBall> &fireBalls, std::list<Exp> &exps )
{
    SetDir();
    Map.MapMove( -a_x, -a_y );
    for( auto &enemy : enemies ) enemy.Change( -a_x, -a_y );
    for( auto &exp : exps ) exp.Change( -a_x, -a_y );
    for( auto &orb : orbs ) orb.Change( -a_x, -a_y );
    for( auto &fireBall : fireBalls ) fireBall.Change( -a_x, -a_y );
}

void Player::SetPower( int x, int frame )
{
    MyPower[x] = 1;
    StartCD[x] = frame;
}
int Player::GetPower( int x ){return MyPower[x];}
void Player::SetCD( int t, int x ){ CD[t] = x; }
int Player::GetCD( int t ){ return CD[t]; }
void Player::SetStartCD( int t, int x ){ StartCD[t] = x; }
int Player::GetStartCD( int t ){ return StartCD[t]; }

void Player::SetHealthBar()
{
    Health.texture = pre::HealthTexture;
    HealthBar.texture = pre::HealthBarTexture;
    Health.rectst = {0, 0, HealthBarWidth, HealthBarHeight};
    HealthBar.rectst = {0, 0, HealthBarWidth, HealthBarHeight};
    Health.rect = {CENTER_X-40,CENTER_Y+this->rect.h/2+10, HealthBarWidth, HealthBarHeight};
    HealthBar.rect = {CENTER_X-40,CENTER_Y+this->rect.h/2+10, HealthBarWidth, HealthBarHeight};
}

void Player::Bleeding( int dmg )
{
    HP -= dmg;
    double per = double(HP)/HPMax;
    Health.rectst.w = double(HealthBarWidth)*per;
    Health.rect.w = double(HealthBarWidth)*per;
}

void Player::renderPlayer(){
    this->drawObj();
    Health.drawObj();
    HealthBar.drawObj();
}
