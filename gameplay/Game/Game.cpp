#include "Game.hpp"

Game::Game()
{
    memset(pre::OptionUsed, 0, sizeof(pre::OptionUsed));
    memset(Dot, 0, sizeof(Dot));
}

Game::~Game()
{
    enemies.clear();
    orbs.clear();
    fireBalls.clear();
    exps.clear();
}

void Game::play( int MapChoice ){
    MapTerrain = MapChoice;
    Prepare();
    Mix_PlayChannel(0, ThemeSound, -1);

//    player.MyPower[0] = 4;
//    player.MyPower[1] = 4;
//    player.MyPower[2] = 1;

    bool ok = 1;
    Exp exp;
    exp.SetUp( CENTER_X,CENTER_Y , -1);
    exps.push_back( exp );

    int GameState = 0;
    int Upgrades = 0;
    bool GameQuit = false, GameWin = false;
    while(!GameQuit)
    {
        TimeManager::Instance()->process();
        int currentTime = SDL_GetTicks();

        while(SDL_PollEvent(&base::g_event))
        {
            if (base::g_event.type == SDL_QUIT){GameQuit = Quit = true;break;}
            switch (GameState)
            {
                case 0 :
                    pause.CheckMouse(base::g_event);
                    if(pause.status == 1) {GameState = 1; Mix_Pause(-1); }
                    break;
                case 1 :
                    home.CheckMouse(base::g_event);
                    if(home.status == 1){GameQuit = true; break;}
                    resume.CheckMouse(base::g_event);
                    if(resume.status == 1){GameState = 0; Mix_Resume(-1); }
                    break;
                case 2 :
                    for(int i = 0; i <= 2; i++) card[i].CheckMouse(base::g_event);
                    for(int i = 0; i <= 2; i++)
                        if( card[i].status == 1 )
                        {
                            card[i].Update(player);
                            Upgrades--;
                            if(Upgrades <= 0) GameState = 0;
                            for(int i = 0; i <= 2; i++) card[i].content = -1;
                        }
                    break;
            }
        }
        if(GameState == 2)
        {
            LevelUp();
            int frameTime = SDL_GetTicks() - currentTime;
            if( frameTime < TimeStep ) SDL_Delay( TimeStep-frameTime );
            continue;
        }
        if(GameState == 1)
        {
            PauseGame();
            int frameTime = SDL_GetTicks() - currentTime;
            if( frameTime < TimeStep ) SDL_Delay( TimeStep-frameTime );

            continue;
        }
        if(GameState == 0)
        {
            //update timeclock
            timecount.UpdateTime();
            wave.SetWave(int(timecount.minute), int(timecount.second) );
            // nhap thao tac tu ban phim
            player.ResetInput();
            player.KeyInput();
            // random sinh quai
            SpawnEnemy();
            // xu ly dan (neu co)
            Firing();
            //xu ly move cac Obj
            MoveAll();

            //cac obj move
            for( auto &enemy : enemies) enemy.MoveOccupy( enemies );

            for( auto &orb : orbs )
                if( orb.delayTime <= 0 ) orb.Run();
                else orb.delayTime -= TimeStep;
            for( auto &fireBall : fireBalls )
                if( fireBall.delayTime <= 0 ) fireBall.Run();
                else fireBall.delayTime -= TimeStep;

            //boss move
            if( boss.exist == 1 ) boss.Doing();


            //Hap thu kinh nghiem
            for( auto &exp : exps )
                if(exp.exist == true) {
                    Upgrades += player.ExpAbsorb( exp );
                    if( Upgrades ) GameState = 2;
                }



            // kiem tra va cham
            PowerColision();

            // kiem tra dan exist
            PowerExisted();

            // render
            RenderGamePlay( 1 );
            pause.drawObj();
            SDL_RenderPresent(base::renderer);

            SDL_RenderClear(base::renderer);

            if( player.HP <= 0 ) break;

            //xoa quai va dan
            RemoveThing();

            int frameTime = SDL_GetTicks() - currentTime;
            if( frameTime < TimeStep ) SDL_Delay( TimeStep-frameTime );
    //        break;
        }
    }
    Mix_HaltChannel(-1);
    if( player.HP <= 0 ){
        Screen GameOver;
        GameOver.SetTexture(std::string("GameOver.png"));
        GameOver.rect.w = SCREEN_WIDTH;
        GameOver.rect.h = SCREEN_HEIGHT;
        GameOver.drawObj();
        SDL_RenderPresent(base::renderer);
        SDL_Delay(5000);
    }
    return ;
}

void Game::Prepare()
{
    LoadAll preload;
    preload.loading( MapTerrain );

    Map.SetMap();

//    Button pause;
    pause.texture = base::Load_Image("./asset/Screen/Pause.png");
    pause.rectst = {0, 0, 131, 116};
    pause.rect = {SCREEN_WIDTH-80,0, 80, 80};

//    Button resume;
    resume.texture = base::Load_Image("./asset/Screen/Resume.png");
    resume.rectst = {0, 0, 401, 102};
    resume.rect = {CENTER_X+300-200-20, CENTER_Y+250-50-20, 200, 50};

//    Button home;
    home.texture = base::Load_Image("./asset/Screen/Home.png");
    home.rectst = {0, 0, 131, 116};
    home.rect = {CENTER_X+300-200-60-20,CENTER_Y+250-50-20, 50, 50};

//    Screen PauseMenu;
    PauseMenu.texture = base::Load_Image("./asset/Screen/PauseMenu.png");
    PauseMenu.rectst = {0, 0, 624, 480};
    PauseMenu.rect = {CENTER_X-300, CENTER_Y-250, 600, 500};

    player.SetUp();
    wave.SetUp("./asset/Enemy/Wave.txt");
    TimeManager::Instance()->reset();

    switch (MapTerrain)
    {
    case 0 :
        ThemeSound = Mix_LoadWAV("./asset/MenuTheme.WAV");
        break;

    case 1 :
        ThemeSound = Mix_LoadWAV("./asset/GraveYardTheme.ogg");
        break;

    case 2 :
        ThemeSound = Mix_LoadWAV("./asset/VolcanoTheme.ogg");
        break;
    }
    HitSound = Mix_LoadWAV("./asset/Sound/Hit.WAV");
}

void Game::MoveAll()
{
    double a_x, a_y;
    player.Move( a_x, a_y );
    Map.MapMove( -a_x, -a_y );
    for( auto &enemy : enemies ) {enemy.ChangeOccupy( -a_x, -a_y, enemies ); enemy.SetOccupy();}
    for( auto &exp : exps ) exp.Change( -a_x, -a_y );
    for( auto &orb : orbs ) orb.Change( -a_x, -a_y );
    for( auto &fireBall : fireBalls )
        if(fireBall.delayTime <= 0) fireBall.Change( -a_x, -a_y );
    boss.Change( -a_x, -a_y );
}

void Game::LevelUp()
{
    RenderGamePlay( 0 );
    bool xd[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ;
    for(int i = 0; i <= 2; i++) if(card[i].content == -1){
        card[i].Appear(i-1);
        while(xd[card[i].content])
        {
            card[i].Random();
        }
        xd[card[i].content] = 1;
    }
    for(int i = 0; i <= 2; i++) card[i].drawObj();
    SDL_RenderPresent(base::renderer);
}

void Game::SpawnEnemy()
{
//    if(wave.WaveNum < wave.MaxWave ){
    if(wave.WaveNum < 2){
        if( wave.WaveNum > CurrentWave.second )
            CurrentWave.first += wave.GetAmount(), CurrentWave.second = wave.WaveNum;
//        CurrentWave.first = 10;
        if( int(SDL_GetTicks()) - timeSpawn.first > timeSpawn.second && enemies.size() < wave.GetAmount() ){
            int number = func::random( 1, 5 );
            for( int i = 1; i <= number; i++ ){
                for( int j = 1; j <= 10; j++ ){
                    Enemy enemy;
                    int type = wave.GetEnemy();
                    int dif =  50;
                    int edge = func::random(1, 4);
                    if( edge == 1 ) enemy.SetUp( (func::random(0, SCREEN_WIDTH)), -dif, type);
                    if( edge == 2 ) enemy.SetUp( -dif, (func::random(0, SCREEN_HEIGHT) ), type);
                    if( edge == 3 ) enemy.SetUp( (func::random(0, SCREEN_WIDTH) ), SCREEN_HEIGHT+dif, type);
                    if( edge == 4 ) enemy.SetUp( SCREEN_WIDTH+dif, (func::random(0, SCREEN_HEIGHT) ), type);
                    enemy.SetOccupy();
                    if(enemy.CheckOccupy( enemies ) == 0)
                    {
                        enemies.push_back( enemy );
                        break;
                    }
                }
                timeSpawn.first = SDL_GetTicks();
            }
        }

    }
    else{
        if( boss.exist == 0 ){
            int dif = 500;
            int edge = func::random(1, 4), x, y;
            if( edge == 1 ) x = func::random(0, SCREEN_WIDTH),  y = -dif;
            if( edge == 2 ) x = -dif,                           y = func::random(0, SCREEN_HEIGHT);
            if( edge == 3 ) x = func::random(0, SCREEN_WIDTH),  y = SCREEN_HEIGHT+dif;
            if( edge == 4 ) x = SCREEN_WIDTH+dif,               y = (func::random(0, SCREEN_HEIGHT) );
            boss.SetUp(x, y, MapTerrain);
            boss.SetState();
            boss.SetPhaseClip();
        }
        if( boss.exist == 1 && boss.BossType == 1 && boss.phaseState == 4 && boss.SummonWave > 0 )
        {
            int NUM = 20; int R = 600;
            double angle = 0;
            for( int i = 0; i < NUM; i ++ )
            {
                angle += 360/NUM;
                std::pair<int, int> luu = func::GetPosCircle(angle, R);
                Enemy enemy;
                int type = 0;
                enemy.SetUp( CENTER_X+luu.first, CENTER_Y+luu.second, type);
                enemy.SetOccupy();
                enemy.IsThrough = true;
                enemy.aim_x = CENTER_X;
                enemy.aim_y = CENTER_Y;
                enemy.v_Obj = 80;
                enemies.push_back( enemy );
            }
            boss.SummonWave --;
        }
    }
}

void Game::Firing()
{
    if( player.GetPower(0) && player.checkCD(0)  ){
        OrbAdd( orbs, player.MyPower[0], player.dir );
        player.SetStartCD(0);
    }
    if( player.GetPower(1) && player.checkCD(1) ){
        int f_x = 1e9, f_y = 1e9; double luu = 1e9;
        for(auto &enemy : enemies) if(luu > func::dist(CENTER_X, CENTER_Y, enemy.c_x, enemy.c_y) )
            {
                luu = func::dist(CENTER_X, CENTER_Y, enemy.c_x, enemy.c_y);
                f_x = enemy.c_x; f_y = enemy.c_y;
            }
        if(boss.exist == 1)
        {
            if( luu > func::dist(CENTER_X, CENTER_Y, boss.c_x, boss.c_y) )
            {
                luu = func::dist(CENTER_X, CENTER_Y, boss.c_x, boss.c_y);
                f_x = boss.c_x; f_y = boss.c_y;
            }
        }
        if( luu != 1e9 ) FireBallAdd( fireBalls, player, f_x, f_y );
    }
    if( player.GetPower(2) )
    {
        ZoneAdd(zone, player);
    }
}

void Game::PowerColision()
{
    for( auto &enemy : enemies )
    {
        for( auto &orb : orbs )
            {
            if( func::checkRect( orb.GetRect(), enemy.GetRect() ) )
            {
                orb.exist = 0;
                enemy.HP -= orb.damage;
                Dmg dmg( orb.damage, enemy.rect.x, enemy.rect.y );
                dmgs.push_back( dmg );
                orb.SetTexture(std::string("orb_explode.png"));
            }
        }
        for( auto &fireBall : fireBalls )
            {
            if( func::checkRect( fireBall.GetRect(), enemy.GetRect() ) )
            {
                fireBall.exist = 0;
                enemy.HP -= fireBall.damage;
                Dmg dmg( fireBall.damage, enemy.rect.x, enemy.rect.y );
                dmgs.push_back( dmg );
                fireBall.SetTexture(std::string("FireBall_explode.png"));
            }
        }
        if( player.GetPower( 2 ) && zone.CanDmg == 1 ){
            if( zone.DOT( enemy ) )
            {
                Dmg dmg( zone.damage, enemy.rect.x, enemy.rect.y );
                dmgs.push_back( dmg );
            }
        }

        if(enemy.exist == true && base::CanChoose == true && enemy.RectOccupy.checkRect( base::CenterRect ) ){
            if(enemy.CoolDown == EnemyCD ) {
                player.Bleeding(enemy.damage);
                if( player.HP <= 0 ) break;
            }
            enemy.CoolDown -= TimeStep;
            if(enemy.CoolDown <= 0 ) enemy.CoolDown = EnemyCD;
        }
        if( player.kameha.state == 2 )
        {
            int KameDmg = player.kameha.CheckDmg(enemy.rect);
            if( KameDmg )
            {
                enemy.HP -= KameDmg;
                Dmg dmg( KameDmg, enemy.rect.x, enemy.rect.y );
                dmgs.push_back( dmg );
            }
        }
    }

    // kiem tra voi boss
    if( boss.Invicible == false ){
        SDL_Rect bossRect = boss.GetBossBody();
        for( auto &orb : orbs )
            {
            if( func::checkRect( orb.GetRect(), bossRect ) )
            {
                orb.exist = 0;
                boss.HP -= orb.damage;
                Dmg dmg( orb.damage, bossRect.x, bossRect.y );
                dmgs.push_back( dmg );
                orb.SetTexture(std::string("orb_explode.png"));
            }
        }
        for( auto &fireBall : fireBalls )
            {
            if( func::checkRect( fireBall.GetRect(), bossRect ) )
            {
                fireBall.exist = 0;
                boss.HP -= fireBall.damage;
                Dmg dmg( fireBall.damage, bossRect.x, bossRect.y );
                dmgs.push_back( dmg );
                fireBall.SetTexture(std::string("FireBall_explode.png"));
            }
        }
        if( player.GetPower( 2 ) && zone.CanDmg == 1 ){
            if( zone.DOT( boss ) )
            {
                Dmg dmg( zone.damage, bossRect.x, bossRect.y );
                dmgs.push_back( dmg );
            }
        }
        if(boss.exist == true && base::CanChoose == true && func::checkRect(bossRect, player.GetRect() )  ){
            if(boss.CoolDown == BossCD ) {
                player.Bleeding(boss.damage);
            }
            boss.CoolDown -= TimeStep;
            if(boss.CoolDown <= 0 ) boss.CoolDown = BossCD;


            if( boss.BossType == 0 ){
                if( boss.phaseState == 3 )
                {
                    if( boss.SkillHit == false )
                    {
                        player.Bleeding(boss.dmgSkill);
                        boss.SkillHit = true;
                    }
                }
                else boss.SkillHit = false;
            }
        }
        if( player.kameha.state == 2 )
        {
            int KameDmg = player.kameha.CheckDmg(bossRect);
            if( KameDmg )
            {
                boss.HP -= KameDmg;
                Dmg dmg( KameDmg, bossRect.x, bossRect.y );
                dmgs.push_back( dmg );
            }
        }
        if( boss.BossType == 2 && boss.kameha.state == 2 && player.phaseState != 2 )
        {
            int KameDmg = boss.kameha.CheckDmg(base::CenterRect);
            if( KameDmg && player.IsKame.first == 0 )
            {
                player.Bleeding(KameDmg);
                if( player.IsKame.first >= player.IsKame.second ) player.IsKame.first = 0;
                else player.IsKame.first += TimeStep;

//                Dmg dmg( KameDmg, bossRect.x, bossRect.y );
//                dmgs.push_back( dmg );
                boss.IsAbove = 1000;
            }
        }
        if(player.phaseState == 2 ) boss.IsAbove = 0;
        if( boss.IsAbove > 0 ) boss.IsAbove -= TimeStep;
        else boss.IsAbove = 0;

    }
}

void Game::PowerExisted()
{
    for( auto &orb : orbs ) {
        orb.ExistTime -= TimeStep;
        if( orb.ExistTime <= 0 ){
            orb.exist = 0;
            orb.SetTexture(std::string("orb_explode.png"));
        }
    }

    for( auto &fireBall : fireBalls ) {
        fireBall.ExistTime -= TimeStep;
        if( fireBall.ExistTime <= 0 ){
            fireBall.exist = 0;
            fireBall.SetTexture(std::string("orb_explode.png"));
        }
    }

}

void Game::PauseGame()
{
    RenderGamePlay( 0 );
    PauseMenu.drawObj();
    resume.drawObj();
    home.drawObj();
    SDL_RenderPresent(base::renderer);
}

void Game::RenderGamePlay( int IsMoving )
{
    Map.drawObj();
    for( auto &orb : orbs ) if(orb.delayTime <= 0) orb.drawObj();
    for( auto &fireBall : fireBalls ) if( fireBall.delayTime <= 0 ) fireBall.RenderMoving( IsMoving, 0, 1 );
    zone.drawObj();
    for( auto &exp : exps ) exp.drawObj();

    if( boss.IsAbove == 0 && boss.exist == 1 ) boss.Print(IsMoving);

    player.renderPlayer( IsMoving );
//    for( auto &enemy : enemies) enemy.drawObj();
    for( auto &enemy : enemies) enemy.RenderMoving( IsMoving, 1, 0 );
    if( boss.IsAbove > 0 && boss.exist == 1 ) boss.Print(IsMoving);


    for( auto &dmg : dmgs ) {
        if( dmg.HaveSound == false ){
            Mix_PlayChannel(1, HitSound, 0);
            dmg.HaveSound = true;
        }
        if( DmgAppear == true ) dmg.PopUp(IsMoving);
    }
    timecount.Display();
    killcount.Display();
}

void Game::RemoveThing()
{
    auto orb = orbs.begin();
    while (orb != orbs.end()) {
        if (orb->exist <= 0) orb = orbs.erase(orb);
        else ++orb;
    }
//    delete orb;
    auto fireball = fireBalls.begin();
    while (fireball != fireBalls.end()) {
        if (fireball->exist <= 0) fireball = fireBalls.erase(fireball);
        else ++fireball;
    }
//    delete fireball;
    auto enemy = enemies.begin();
    while (enemy!= enemies.end()){
        if(enemy->HP <= 0) {
            Exp exp;
            exp.SetUp(enemy->GetRect().x, enemy->GetRect().y, -1);
            exps.push_back( exp );
            enemy = enemies.erase(enemy);
            killcount.Add();
        }
        else ++enemy;
    }
//    delete enemy;
    auto exp = exps.begin();
    while (exp!= exps.end()){
        if(exp->exist == 0) {
            exp = exps.erase(exp);
        }
        else ++exp;
    }
//    delete exp;
    auto dmg = dmgs.begin();
    while (dmg!= dmgs.end()){
        if(dmg->exist == 0) {
            dmg = dmgs.erase(dmg);
        }
        else ++dmg;
    }
//    delete dmg;
}


