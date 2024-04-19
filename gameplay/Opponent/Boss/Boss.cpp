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

            // nhap thong so Boss
            v_Obj = 30; v_Fly = 60;
            damage = 5; dmgSkill = 20;
            HP = 400;

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

            // nhap thong so Boss
            v_Obj = 30; v_Fly = 60;
            damage = 5; dmgSkill = 20;
            HP = 400;
            SummonWave = 1;
            break;
        }
        case 2 :
        {
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
            }
            else
            if( phaseState == 4 ){
                double Dist = func::dist(aim_x , aim_y, c_x, c_y );
                if( Dist == 0 ) return;
                Change(( v_Obj*(CENTER_X-c_x)/Dist ), ( v_Obj*(CENTER_Y-c_y)/Dist ) );
                Located();
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
            }
            Located();
            break;
        }
        case 1 :
        {
            // 0 Disappearing 1 Invisible 2 Appearing 3 Standing 4 Summoning 5 Moving
            if(phaseState >= 1 && phaseState <= 2)
            {
                Change(a_x_Fly, a_y_Fly);
                Located();
            }
            else
            if(phaseState == 3)
            {
                // standing
            }
            else
            if(phaseState == 4)
            {
                // standing
            }
            else
            if(phaseState == 5){
                double Dist = func::dist(aim_x , aim_y, c_x, c_y );
                if( Dist == 0 ) return;
                Change(( v_Obj*(CENTER_X-c_x)/Dist ), ( v_Obj*(CENTER_Y-c_y)/Dist ) );
                Located();
                SummonWave = 1;
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
            }
            Located();
            break;
        }
        case 2 :
        {
            break;
        }
    }
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
