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
    this->rect.x = CENTER_X - 15;
    this->rect.y = CENTER_Y - 9;
    this->rect.w = 30;
    this->rect.h = 18;
    this->texture = pre::PlayerTexture;
    this->dir = 1;
    SetHealthBar();
    SetExpBar();
    // dung de enemy bi can boi player
    int dis = 5;
    base::CenterRect = {rect.x+dis, rect.y+dis, rect.w-dis*2, rect.h-dis*2};
}

void Player::ResetInput(){ a_x = 0; a_y = 0; }

void Player::KeyInput()
{
    const Uint8* state = SDL_GetKeyboardState(nullptr);
    if( state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP] )       a_y -= v_Player*GameSpeed;
    if( state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN] )     a_y += v_Player*GameSpeed;
    if( state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT] )     a_x -= v_Player*GameSpeed;
    if( state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT] )    a_x += v_Player*GameSpeed;
//    if( state[SDL_SCANCODE_H] && state[SDL_SCANCODE_I] && state[SDL_SCANCODE_E] && state[SDL_SCANCODE_N] )
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

void Player::Move( Screen &Map, std::list<Enemy> &enemies, std::list<Orb> &orbs, std::list<FireBall> &fireBalls, std::list<Exp> &exps, Boss &boss )
{
    SetDir();
    Map.MapMove( -a_x, -a_y );
    for( auto &enemy : enemies ) {enemy.ChangeOccupy( -a_x, -a_y, enemies ); enemy.SetOccupy();}
    for( auto &exp : exps ) exp.Change( -a_x, -a_y );
    for( auto &orb : orbs ) orb.Change( -a_x, -a_y );
    for( auto &fireBall : fireBalls )
        if(fireBall.delayTime <= 0) fireBall.Change( -a_x, -a_y );

    boss.Change( -a_x, -a_y );
}

void Player::SetPower( int x )
{
    MyPower[x] = 1;
}
int Player::GetPower( int x ){return MyPower[x];}
void Player::SetCD( int t, int x ){ CD[t] = x; }
int Player::GetCD( int t ){ return CD[t]; }

void Player::SetHealthBar()
{
    Health.texture = pre::HealthTexture;
    Health.rectst = {0, 0, HealthBarWidth, HealthBarHeight};
    Health.rect = {CENTER_X-40,CENTER_Y+this->rect.h/2+10, HealthBarWidth, HealthBarHeight};
    HealthBar.texture = pre::HealthBarTexture;
    HealthBar.rectst = {0, 0, HealthBarWidth, HealthBarHeight};
    HealthBar.rect = {CENTER_X-40,CENTER_Y+this->rect.h/2+10, HealthBarWidth, HealthBarHeight};
}

void Player::SetExpBar()
{
    ExpPoint.texture = pre::ExpPointTexture;
    ExpPoint.rectst = {0, 0, ExpBarWidth, ExpBarHeight};
    ExpPoint.rect = {0, SCREEN_HEIGHT-20, 0, 20};
    ExpBar.texture = pre::ExpBarTexture;
    ExpBar.rectst = {0, 0, ExpBarWidth, ExpBarHeight};
    ExpBar.rect = {0, SCREEN_HEIGHT-20, SCREEN_WIDTH, 20};
}

void Player::Bleeding( int dmg )
{
    HP -= Defense*dmg;
    double per = double(HP)/HPMax;
//    Health.rectst.w = double(HealthBarWidth)*per;
    Health.rect.w = double(HealthBar.rect.w)*per;
}

int Player::ExpAbsorb( Exp &exp )
{
    if( func::dist( exp.c_x, exp.c_y, CENTER_X, CENTER_Y) <= 10 ){
        EXP += ExpGain*exp.stat;
        exp.exist = 0;

        int addLevel = 0;
        while( EXP >= ExpRequire[Level] )
        {
            EXP -= ExpRequire[Level];
            addLevel++;
            Level++;
        }

        double per = double(EXP)/ExpRequire[Level];
        ExpPoint.rect.w = double(ExpBar.rect.w)*per;
        return addLevel;
    }
    if( func::dist( exp.c_x, exp.c_y, CENTER_X, CENTER_Y) <= PlayerR ) {
        exp.Chase();
        return 0;
    }
    return 0;
}

void Player::renderPlayer(){
    this->drawObj();
    Health.drawObj();
    HealthBar.drawObj();
    ExpPoint.drawObj();
    ExpBar.drawObj();
}

void Player::SetStartCD( int t ){ StartCD[t] = SDL_GetTicks(); }
int Player::GetStartCD( int t ){ return StartCD[t]; }

int Player::checkCD(int t)
{
    if( StartCD[t] == -1 ){
        return 1;
    }else{
        if( int(SDL_GetTicks()) - StartCD[t] >= CD[t] ){
            return 1;
        }
        return 0;
    }
}
