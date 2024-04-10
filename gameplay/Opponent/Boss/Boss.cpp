#include "Boss.hpp"

Boss::Boss()
{
    v_Obj = 30; v_Fly = 60;
    damage = 5; dmgSkill = 20;
    HP = 400;
    exist = 0;
}

Boss::~Boss()
{

}

void Boss::SetUp( int x, int y )
{
//    phaseFrame = { {4, 0.1}, {2, 0.1}, {1, 0.1}, {7, 0.1}, {6, 0.15} };
//    phaseTime = { 0.5, 0.2, 3, 0.7, 5 };
    // 0 prepare; 1 jumping; 2 floating; 3 landing; 4 moving

    for( int i = 0; i < 5; i++ ) NumF += phaseFrame[i].first;
    RectOccupy = { 42, 92, 258-42, 257-92 };
    SetTexture(std::string("./asset/Enemy/SlimeBoss.png"));

    timeCurrent = 0;
    phaseState =  4;

    SDL_QueryTexture(texture, NULL, NULL, &rectst.w, &rectst.h);
    exist = 1;

    //xet clip cho tung phase
    int X = 0, Y = 0, W = rectst.w/NumF, H = rectst.h;
    for( int t = 0; t < 5; t++)
        for( int i = 0; i < phaseFrame[t].first; i++ )
        {
            phaseRect[t][i] = { X, Y, W, H };
            X+=W;
        }

    rect.x = x; rect.y = y;
    rect.w = W; rect.h = H;
    Located();
    SetL();

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
        phaseState ++; phaseState%=5;
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


    if(phaseState >= 1 && phaseState <= 3)
    {
        double Dist = func::dist(aim_x , aim_y, c_x, c_y );
        if( Dist == 0 ) return;
        Change(( v_Fly*(aim_x-c_x)/Dist ), ( v_Fly*(aim_y-c_y)/Dist ) );
        Located();
    }
    else
    if( phaseState == 4 ){
        double Dist = func::dist(aim_x , aim_y, c_x, c_y );
        if( Dist == 0 ) return;
        Change(( v_Obj*(aim_x-c_x)/Dist ), ( v_Obj*(aim_y-c_y)/Dist ) );
        Located();
    }
    else
    if( phaseState == 0 ){
        double Dist = func::dist(aim_x , aim_y, c_x, c_y );
        if( Dist == 0 ) return;
        v_Fly = Dist/(phaseTime[1] + phaseTime[2] +phaseTime[3]);
        aim_x = CENTER_X;
        aim_y = CENTER_Y;
    }
    Located();
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
