#include "Player.hpp"
Player::Player()
{

}

Player::~Player()
{

}

void Player::SetUp()
{
    // nhap texture
    std::string SlimePath = "./asset/Player/Slime0.png";    SlimePath[20] = char(SkinOption+'0');
    SetTexture(SlimePath);
    // nhap thong so cac phase
    NumPhase = 3; // 0 standing 1 moving 2 jumping
    phaseFrame[0] = {8, 0.1};
    phaseFrame[1] = {7, 0.1};
    phaseFrame[2] = {11, 0.1};
    phaseFrame[2].second = (double(FlyTime.second)/1000)/phaseFrame[2].first;

    for( int i = 0; i < NumPhase; i++ ) NumF += phaseFrame[i].first;

    // nhap thoi gian va phase bat dau
    timeCurrent = 0;
    phaseState =  0;

    // nhap rect va xet clip cho tung phase
//    RectOccupy = { 7, 144, 108, 223 };
    SDL_QueryTexture(texture, NULL, NULL, &rectst.w, &rectst.h);

    int X = 0, Y = 0, W = rectst.w/NumF, H = rectst.h;
    for( int t = 0; t < NumPhase; t++)
        for( int i = 0; i < phaseFrame[t].first; i++ )
        {
            phaseRect[t][i] = { X, Y, W, H };
            X+=W;
        }
    rect.x = CENTER_X-W/2; rect.y = CENTER_Y-91*H/111;
    rect.w = W; rect.h = H;
    // dung de enemy bi can boi player, occupyrect
    Body = { CENTER_X - 48/2, CENTER_Y - 36/2, 48, 36 };
    base::CenterRect = Body;
    base::CenterRect.x += 5;
    base::CenterRect.y += 5;
    base::CenterRect.w -= 5*2;
    base::CenterRect.h -= 5*2;
    SetPhaseClip();

    this->dir = 1;
    SetHealthBar();
    SetExpBar();
}

void Player::ResetInput(){ a_x = 0; a_y = 0; }

void Player::KeyInput()
{
    const Uint8* state = SDL_GetKeyboardState(nullptr);
    if( phaseState != 2 ){
        // neu ko jumping thi duoc kameha
        switch (kameha.state)
        {
            case 0:
            {
                if( state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP] )       a_y -= v_Player;
                if( state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN] )     a_y += v_Player;
                if( state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT] )     a_x -= v_Player;
                if( state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT] )    a_x += v_Player;
                if( a_x && a_y ) a_x/=1.414, a_y/=1.414;

                if( state[SDL_SCANCODE_L] && !state[SDL_SCANCODE_O] ) kameha.state = 1, kameha.IsStateChange = true;
    //            if( state[SDL_SCANCODE_L] && state[SDL_SCANCODE_O] ) kameha.state = 0, kameha.IsStateChange = false;
                if( state[SDL_SCANCODE_J] ) {
                    if( JumpCD.first <= 0 ){
                        phaseState = 2;
                        SetPhaseClip();
                        JumpCD.first = JumpCD.second;
                    }
                }
                if( JumpCD.first > 0 ) JumpCD.first -= TimeStep;
                break;
            }
            case 1:
            {
                if( state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP] )       aimDir --;
                if( state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN] )     aimDir ++;
                aimDir = (aimDir%360 + 360)%360;
                if( !state[SDL_SCANCODE_L] ) {
                    kameha.state = 2;
                    kameha.IsStateChange = true;
                    HP /= 2;
                    Health.rect.w /= 2;
                }
                if( state[SDL_SCANCODE_O] ) kameha.state = 0, kameha.IsStateChange = false;
                break;
            }
            case 2:
            {
                kameha.StartRelease += TimeStep;
                if( kameha.StartRelease >= kameha.EndRelease )
                {
                    kameha.StartRelease = 0;
                    kameha.state = 0, kameha.IsStateChange = true;
                }
                break;
            }
        }
    }
    else{
        if( state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP] )       a_y -= v_Player;
        if( state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN] )     a_y += v_Player;
        if( state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT] )     a_x -= v_Player;
        if( state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT] )    a_x += v_Player;
        if( a_x && a_y ) a_x/=1.414, a_y/=1.414;
    }
//    SetPhaseClip();
}

void Player::SetState()
{
    bool IsChange = false;
    bool Landing = false;
    if(phaseState!=2)
    {
        if(a_x!=0 || a_y!=0) {
            if(phaseState != 1){
                phaseState = 1;
                IsChange = true;
            }
        }
        else {
            if( phaseState ){
                phaseState = 0;
                IsChange = true;
            }
        }
    }
    switch (phaseState)
    {
        case 2:
        {
            FlyTime.first += TimeStep;
            if( FlyTime.first >= FlyTime.second )
            {
                FlyTime.first = 0;
                phaseState = 0;
                IsChange = true;
                Landing = true;
                v_Player = v_Move;
            }else{
                v_Player = v_Jump;
            }
            break;
        }
        case 1:
        {
            v_Player = v_Move;
            break;
        }
        case 0:
        {
//            v_Player = v_Stand;
            break;
        }
    }
    if(IsChange == true)    SetPhaseClip();
    if( phaseState == 2 ) base::CanChoose = false;
    else base::CanChoose = true;
}
void Player::SetPhaseClip()
{
//    std::cout << phaseState << '\n';
    frameNum = phaseFrame[phaseState].first;
    frameTime = phaseFrame[phaseState].second;
    for( int i = 0; i < frameNum; i++ )
    {
        clip[i] = phaseRect[phaseState][i];
    }
    timeCurrent = 0;
}

void Player::Print( bool IsMoving )
{
    SetState();
    if( a_x < 0 ) IsFlip = true;
    if( a_x > 0 ) IsFlip = false;
    if( IsMoving == false )
    {
        SDL_RendererFlip flip = SDL_FLIP_NONE;
        if( IsFlip == true ) flip = SDL_FLIP_HORIZONTAL;
        SDL_RenderCopyEx(base::renderer, texture, &rectst, &rect, 0, nullptr, flip);
    }
    else
    {
        //lay frame cua animation theo thoi gian
        timeCurrent += TimeManager::Instance()->getElapsedTime();
        while( timeCurrent >= frameTime*frameNum ) timeCurrent -= frameTime*frameNum;
        int clipIndex = timeCurrent/frameTime;

        SDL_RendererFlip flip = SDL_FLIP_NONE;
        if( IsFlip == true ) flip = SDL_FLIP_HORIZONTAL;

        SDL_RenderCopyEx(base::renderer, texture, &clip[clipIndex], &rect, 0, nullptr, flip);

        // gan lai frame hien tai
        rectst = clip[clipIndex];
    }
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

void Player::Move( double &ax, double &ay )
{
    SetDir();
    ax = a_x; ay = a_y;
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
    Health.rect = {CENTER_X-HealthBarWidth/2,this->rect.y+this->rect.h+10, HealthBarWidth, HealthBarHeight};
    HealthBar.texture = pre::HealthBarTexture;
    HealthBar.rectst = Health.rectst;
    HealthBar.rect = Health.rect;
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
        switch (exp.type)
        {
            case 1 :
            {
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
            case 2 :
            {
                Coin++;
                exp.exist = 0;
                return 0;
            }
            case 3 :
            {
                HP += 10;
                if( HP > HPMax) HP = HPMax;

                double per = double(HP)/HPMax;
                Health.rect.w = double(HealthBar.rect.w)*per;
                exp.exist = 0;
                return 0;
            }
        }
    }
    if( func::dist( exp.c_x, exp.c_y, CENTER_X, CENTER_Y) <= PlayerR ) {
        exp.Chase();
        return 0;
    }
    return 0;
}

void Player::renderPlayer( bool IsMoving ){
//    this->drawObj();
    this->Print( IsMoving );
    Health.drawObj();
    HealthBar.drawObj();
    ExpPoint.drawObj();
    ExpBar.drawObj();


    if( kameha.state == 2 )
    {
        if( kameha.IsStateChange == true ){
            kameha.SetUp( 0 );
            kameha.Aim(CENTER_X,CENTER_Y, aimDir);
            kameha.IsStateChange = false;
        }
        kameha.Firing( IsMoving );
    }
    else if( kameha.state == 1 )
    {
        kameha.SetUp( 0 );
        kameha.Aim(CENTER_X,CENTER_Y, aimDir);
        kameha.Firing( IsMoving );
    }
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
