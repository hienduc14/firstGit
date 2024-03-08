#include "Player.hpp"
Player::Player()
{
    this->rectst = {0, 0, PlayerWidth, PlayerHeight};
    this->rect.x = SCREEN_WIDTH/2 - PlayerWidth/2;
    this->rect.y = SCREEN_HEIGHT/2 - PlayerHeight/2;
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
//    if( state[SDL_SCANCODE_SPACE] ){
//        Ammo* ammo;
//        ammo->SetWH(50, 50);
//        ammo->SetTexture("bullet.png");
//        ammo->SetAmmoType(Ammo::Knife);
//        ammo->SetRect(this->rect.x+PlayerWidth, this->rect.y);
//
//        ammo->SetIsMove(true);
//        std::cout << ammo->GetIsMove() << " ";
//        this->AmmoList.push_back(ammo);
//        std::cout << ammo->GetIsMove() << " " << AmmoList.back()->GetIsMove() << '\n';
//        for(auto it : AmmoList) std::cout << it->GetIsMove() << " "; std::cout << '\n';
//    }
}
void Player::SetDir(){
    if( a_x > 0 || a_y == 0 ) dir = 0;
    if( a_x > 0 || a_y > 0 ) dir = 1;
    if( a_x == 0 || a_y > 0 ) dir = 2;
    if( a_x < 0 || a_y > 0 ) dir = 3;
    if( a_x < 0 || a_y == 0 ) dir = 4;
    if( a_x < 0 || a_y < 0 ) dir = 5;
    if( a_x == 0 || a_y < 0 ) dir = 6;
    if( a_x > 0 || a_y < 0 ) dir = 7;
}

int Player::GetDir(){
    return this->dir;
}

void Player::Move( Map &BackGr, Enemy &enemy )
{
//    this->rect.x += this->a_x;
//    if( rect.x < 0 || rect.x + rect.w > SCREEN_WIDTH )
//        rect.x -= a_x;
//    this->rect.y += this->a_y;
//    if( rect.y < 0 || rect.y + rect.h > SCREEN_HEIGHT )
//        rect.y -= a_y;
    SetDir();
    BackGr.MapMove( -a_x, -a_y );
    enemy.Change( -a_x, -a_y );
}

//
//void Player::SetAmmoList(std::vector<Ammo*> ammoList )
//{
//    AmmoList = ammoList;
//}

//std::vector<Ammo*> Player::GetAmmoList(){ return AmmoList; }
