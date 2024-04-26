#include "Boss.hpp"

Boss::Boss()
{
    exist = 0;
}

Boss::~Boss()
{

}

void Boss::SetUp( int x, int y, int type )
{
    BossType = type;
    switch (type){
        case 0 :
        {
            // nhap texture
            SetTexture(std::string("./asset/Enemy/SlimeBoss.png"));

            // nhap thong so cac phase
            NumPhase = 5; // 0 prepare; 1 jumping; 2 floating; 3 landing; 4 moving
            phaseFrame[0] = {4, 0.1};   phaseTime[0] = 0.5;
            phaseFrame[1] = {2, 0.1};   phaseTime[1] = 0.2;
            phaseFrame[2] = {1, 0.1};   phaseTime[2] = 3;
            phaseFrame[3] = {7, 0.1};   phaseTime[3] = 0.7;
            phaseFrame[4] = {6, 0.15};  phaseTime[4] = 5;

            for( int i = 0; i < NumPhase; i++ ) NumF += phaseFrame[i].first;

            // nhap thoi gian va phase bat dau
            timeCurrent = 0;
            phaseState =  4;
            exist = 1;

            // nhap rect va xet clip cho tung phase
            RectOccupy = { 42, 92, 258-42, 257-92 };
            SDL_QueryTexture(texture, NULL, NULL, &rectst.w, &rectst.h);

            int X = 0, Y = 0, W = rectst.w/NumF, H = rectst.h;
            for( int t = 0; t < NumPhase; t++)
                for( int i = 0; i < phaseFrame[t].first; i++ )
                {
                    phaseRect[t][i] = { X, Y, W, H };
                    X+=W;
                }

            rect.x = x; rect.y = y;
            rect.w = W; rect.h = H;
            Located();
            SetL();
            SetPhaseClip();
            // nhap thong so Boss
            v_Obj = 30; v_Fly = 60;
            damage = 5; dmgSkill = 20;
            HPMax = HP = 601;

            break;
        }
        case 1 :
        {
            // nhap texture
            SetTexture(std::string("./asset/Enemy/GhostBoss.png"));

            // nhap thong so cac phase
            NumPhase = 6; // 0 Disappearing 1 Invisible 2 Appearing 3 Standing 4 Summoning 5 Moving

            phaseFrame[0] = {4, 0.1};   phaseTime[0] = 0.5;
            phaseFrame[1] = {1, 0.1};   phaseTime[1] = 3;
            phaseFrame[2] = {4, 0.2};   phaseTime[2] = 1;
            phaseFrame[3] = {1, 0.1};   phaseTime[3] = 1;
            phaseFrame[4] = {11, 0.1};  phaseTime[4] = 1.5;
            phaseFrame[5] = {5, 0.1};   phaseTime[5] = 5;

            for( int i = 0; i < NumPhase; i++ ) NumF += phaseFrame[i].first;

            // nhap thoi gian va phase bat dau
            timeCurrent = 0;
            phaseState =  5;
            exist = 1;

            // nhap rect va xet clip cho tung phase
            RectOccupy = { 23, 34, 92, 127 };
            SDL_QueryTexture(texture, NULL, NULL, &rectst.w, &rectst.h);

            int X = 0, Y = 0, W = rectst.w/NumF, H = rectst.h;
            for( int t = 0; t < NumPhase; t++)
                for( int i = 0; i < phaseFrame[t].first; i++ )
                {
                    phaseRect[t][i] = { X, Y, W, H };
                    X+=W;
                }

            rect.x = x; rect.y = y;
            rect.w = W; rect.h = H;
            Located();
            SetL();
            SetPhaseClip();

            // nhap thong so Boss
            v_Obj = 30; v_Fly = 60;
            damage = 5; dmgSkill = 20;
            HPMax = HP = 601;
            SummonWave = 1;
            break;
        }
        case 2 :
        {
            // nhap texture
            SetTexture(std::string("./asset/Enemy/FlameBoss.png"));
            // nhap thong so cac phase
            NumPhase = 2; // 0 Moving 1 Kameha in a fixed time and divided to 3 parts ( 1.1 Aiming (Random time) 1.2 Standing (Fixed time)  1.3 Firing (Fixed time) )

            phaseFrame[0] = {7, 0.1};   phaseTime[0] = 5;
            phaseFrame[1] = {6, 0.1};   phaseTime[1] = 6;

            for( int i = 0; i < NumPhase; i++ ) NumF += phaseFrame[i].first;

            // nhap thoi gian va phase bat dau
            timeCurrent = 0;
            phaseState =  0;
            exist = 1;

            // nhap rect va xet clip cho tung phase
            RectOccupy = { 4, 15, 67, 134 };
            SDL_QueryTexture(texture, NULL, NULL, &rectst.w, &rectst.h);

            int X = 0, Y = 0, W = rectst.w/NumF, H = rectst.h;
            for( int t = 0; t < NumPhase; t++)
                for( int i = 0; i < phaseFrame[t].first; i++ )
                {
                    phaseRect[t][i] = { X, Y, W, H };
                    X+=W;
                }

            rect.x = x; rect.y = y;
            rect.w = W; rect.h = H;
            Located();
            SetL();
            SetPhaseClip();
            // nhap thong so Boss
            v_Obj = 60; v_Fly = 60;
            damage = 5; dmgSkill = 20;
            HPMax = HP = 601;
            break;
        }
    }
}

void Boss::SetState()
{
    // get state hien tai
    double ElapseTime = TimeManager::Instance()->getElapsedTime();
    ExistTime += ElapseTime;
    bool changePhase = 0;
    while( ExistTime >= phaseTime[phaseState] )
    {
        ExistTime -= phaseTime[phaseState];
        phaseState = (phaseState + 1)%NumPhase;
//        phaseState ++; phaseState%=NumF;
        changePhase = 1;
    }

    if( changePhase == 1 ) SetPhaseClip();

}

void Boss::SetPhaseClip()
{
    frameNum = phaseFrame[phaseState].first;
    frameTime = phaseFrame[phaseState].second;
    for( int i = 0; i < frameNum; i++ )
    {
        clip[i] = phaseRect[phaseState][i];
    }
    timeCurrent = 0;
}

void Boss::Doing()
{
    SetState();
    switch (BossType){
        case 0 :
        {
            // 0 prepare; 1 jumping; 2 floating; 3 landing; 4 moving
            if(phaseState >= 1 && phaseState <= 3)
            {
                Change(a_x_Fly, a_y_Fly);
                Located();
                if( phaseState == 2 )Invicible = true;
                else Invicible = false;
            }
            else
            if( phaseState == 4 ){
                double Dist = func::dist(aim_x , aim_y, c_x, c_y );
                if( Dist == 0 ) return;
                Change(( v_Obj*(CENTER_X-c_x)/Dist ), ( v_Obj*(CENTER_Y-c_y)/Dist ) );
                Located();
                Invicible = false;
            }
            else
            if( phaseState == 0 ){
                double Dist = func::dist(aim_x , aim_y, c_x, c_y );
                if( Dist == 0 ) return;
                v_Fly = Dist/(phaseTime[1] + phaseTime[2] + phaseTime[3]);
                aim_x = CENTER_X;
                aim_y = CENTER_Y;
                a_x_Fly = v_Fly*(aim_x-c_x)/Dist;
                a_y_Fly = v_Fly*(aim_y-c_y)/Dist;
                Invicible = false;
            }
            Located();

            if( phaseState == 2 )
            {
                IsAbove = 1;
            }else IsAbove = 0;

            break;
        }
        case 1 :
        {
            // 0 Disappearing 1 Invisible 2 Appearing 3 Standing 4 Summoning 5 Moving
            if(phaseState >= 1 && phaseState <= 2)
            {
                Change(a_x_Fly, a_y_Fly);
                Located();
                Invicible = true;
            }
            else
            if(phaseState == 3)
            {
                // standing
                Invicible = false;
            }
            else
            if(phaseState == 4)
            {
                // standing
                Invicible = false;
            }
            else
            if(phaseState == 5){
                double Dist = func::dist(aim_x , aim_y, c_x, c_y );
                if( Dist == 0 ) return;
                Change(( v_Obj*(CENTER_X-c_x)/Dist ), ( v_Obj*(CENTER_Y-c_y)/Dist ) );
                Located();
                SummonWave = 1;
                Invicible = false;
            }
            else
            if( phaseState == 0 ){
                double Dist = func::dist(aim_x , aim_y, c_x, c_y );
                if( Dist == 0 ) return;
                v_Fly = Dist/(phaseTime[1] + phaseTime[2]);
                aim_x = CENTER_X;
                aim_y = CENTER_Y;
                a_x_Fly = v_Fly*(aim_x-c_x)/Dist;
                a_y_Fly = v_Fly*(aim_y-c_y)/Dist;
                Invicible = true;
            }
            Located();
            break;
        }
        case 2 :
        {
            // 0 Moving 1 Kameha in a fixed time and divided to 3 parts ( 1.1 Aiming (Random time) 1.2 Standing (Fixed time) 1.3 Firing (Fixed time) )
            // random second aiming; at least 0.5 second standing; 2.5 second firing
            if( kameha.state == 0 )
            {
                if( MusicPlay == true ){
                    Mix_HaltChannel(3);
                    MusicPlay = false;
                }

            }
            if(phaseState == 1)
            {
                switch (kameha.state)
                {
                    case 0 :
                    {
                        kameha.state = 1;
                        kameha.IsStateChange = true;
                        StartAim = 0;
                    }
                    case 1 :
                    {
                        if(kameha.IsStateChange == true)
                        {
                            aimTime = double(func::random(10, 30))/10;
                            standTime = phaseTime[phaseState] - aimTime - fireTime;
                            kameha.SetUp(1);
                            kameha.IsStateChange = false;
                        }
                        StartAim += TimeManager::Instance()->getElapsedTime();
                        if(aimTime >= StartAim)
                        {
                            kameha.Aim(c_x, c_y, func::GetAngle(CENTER_X-c_x, CENTER_Y-c_y) );
                        }
                        else
                        {
                            kameha.Aim(c_x, c_y, kameha.angle);
                            if( standTime + aimTime >= StartAim )
                            {

                            }
                            else
                            {
                                kameha.state = 2;
                                kameha.IsStateChange = true;
                                StartAim = 0;
                                if( MusicPlay == false ){
                                    Mix_PlayChannel(3, pre::KamehaSound, 0);
                                    MusicPlay = true;
                                }
                            }
                        }


                        break;
                    }
                    case 2 :
                    {
                        if( kameha.IsStateChange == true ){
                            kameha.SetUp(1);
                            kameha.IsStateChange = false;
                        }
                        kameha.Aim(c_x, c_y, kameha.angle);
                        break;
                    }
                }
                Located();
                Invicible = false;
            }
            else
            if( phaseState == 0 ){


                double Dist = func::dist(aim_x , aim_y, c_x, c_y );
                if( Dist == 0 ) return;
                Change(( v_Obj*(CENTER_X-c_x)/Dist ), ( v_Obj*(CENTER_Y-c_y)/Dist ) );
                Located();
                Invicible = false;
                kameha.state = 0;

//                 // dich chuyen
//                if(Dist >= 3000)
//                {
//                    int dif = 500;
//                    int edge = func::random(1, 4), x, y;
//                    if( edge == 1 ) x = func::random(0, SCREEN_WIDTH),  y = -dif;
//                    if( edge == 2 ) x = -dif,                           y = func::random(0, SCREEN_HEIGHT);
//                    if( edge == 3 ) x = func::random(0, SCREEN_WIDTH),  y = SCREEN_HEIGHT+dif;
//                    if( edge == 4 ) x = SCREEN_WIDTH+dif,               y = (func::random(0, SCREEN_HEIGHT) );
//                    double dis_x =x-rect.x, dis_y = y-rect.y;
//                    Change( dis_x, dis_y );
//                }
//                Located();
            }
            Located();
            break;
        }
    }
}

void Boss::Print( bool IsMoving )
{
    switch (BossType)
    {
        case 0 :
        {
            RenderMoving( IsMoving, 1, 0 );
            break;
        }
        case 1 :
        {
            RenderMoving( IsMoving, 1, 0 );
            break;
        }
        case 2 :
        {
            RenderMoving( IsMoving, 1, 0 );
            if( phaseState == 1 ){
                kameha.Firing( IsMoving);
//                std::cout << kameha.state << '\n';
            }
            break;
        }
    }
    SetHealthBar();
    Health.drawObj(); HealthBar.drawObj();
}

SDL_Rect Boss::GetBossBody()
{
    SDL_Rect BossRect = rect;
    BossRect.x += RectOccupy.x;
    BossRect.y += RectOccupy.y;
    BossRect.w = RectOccupy.w;
    BossRect.h = RectOccupy.h;
    return BossRect;
}

void Boss::SetHealthBar()
{
    if( Health.texture == nullptr ){
        int W, H;
        Health.texture = pre::HealthTexture;
        SDL_QueryTexture(Health.texture, nullptr, nullptr, &W, &H );
        Health.rectst = {0, 0, W, H};
        Health.rect = {CENTER_X - 500/2, 90, 500, 40};
        HealthBar.texture = pre::HealthBarTexture;
        HealthBar.rectst = Health.rectst;
        HealthBar.rect = Health.rect;
    }
    double per = double(HP)/HPMax;
    Health.rect.w = HealthBar.rect.w*per;
}
