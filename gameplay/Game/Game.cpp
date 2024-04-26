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
    bool GameQuit = false;
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
                {
                    Pause.CheckMouse(base::g_event);
                    if(Pause.status == 1) {GameState = 1; Mix_Pause(-1); }
                    break;
                }
                case 1 :
                {
                    Home.CheckMouse(base::g_event);
                    if(Home.status == 1){GameQuit = true; GameWin = -1; break;}
                    Resume.CheckMouse(base::g_event);
                    if(Resume.status == 1){GameState = 0; Mix_Resume(-1); }
                    TickBox.CheckTick(base::g_event);
                    if( TickBox.status == 1 ) DmgAppear = false;

                    SoundEFPoint.CheckHold(base::g_event);
                    MusicPoint.CheckHold(base::g_event);
                    double per1 = double(SoundEFPoint.rect.x - SoundEFPoint.limit.x)/SoundEFPoint.limit.w;
                    double per2 = double(MusicPoint.rect.x - MusicPoint.limit.x)/MusicPoint.limit.w;
                    SoundEFVolume.rect.w = per1*SoundEFVolume.rectst.w;
                    MusicVolume.rect.w = per2*MusicVolume.rectst.w;

                    SoundEFPer = per1;
                    MusicPer = per2;
                    Mix_Volume(3, MIX_MAX_VOLUME*SoundEFPer);
                    Mix_Volume(2, MIX_MAX_VOLUME*SoundEFPer);
                    Mix_Volume(1, MIX_MAX_VOLUME*SoundEFPer);
                    Mix_Volume(0, MIX_MAX_VOLUME*MusicPer);
                    break;
                }
                case 2 :
                {
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
                if(exp.exist == true)
                {
                    Upgrades += player.ExpAbsorb( exp );
                    if( Upgrades ) GameState = 2;
                }



            // kiem tra va cham
            PowerColision();

            // kiem tra dan exist
            PowerExisted();

            // render
            RenderGamePlay( 1 );
            Pause.drawObj();
            SDL_RenderPresent(base::renderer);
//            if( !GameQuit )
            SDL_RenderClear(base::renderer);

            if( player.HP <= 0 ) break;

            //xoa quai va dan
            RemoveThing();
            if( boss.exist == true && boss.HP <= 0 ) {
                GameWin = true;
                GameQuit = true;
            }


            int frameTime = SDL_GetTicks() - currentTime;
            if( frameTime < TimeStep ) SDL_Delay( TimeStep-frameTime );
    //        break;
        }
    }
    EndGame();
}

void Game::Prepare()
{
    memset(pre::OptionUsed, 0, sizeof(pre::OptionUsed));
    memset(Dot, 0, sizeof(Dot));
    pre::MapTexture     = pre::Opponent[0][MapTerrain];
    pre::SlimeTexture   = pre::Opponent[1][MapTerrain];
    pre::RabbitTexture  = pre::Opponent[2][MapTerrain];
    pre::BoarTexture    = pre::Opponent[3][MapTerrain];
    switch (MapTerrain)
    {
        case 0 :
        {
            pre::SlimeFrame = 10;
            pre::RabbitFrame = 6;
            pre::BoarFrame = 6;
            break;
        }
        case 1 :
        {
            pre::SlimeFrame = 10;
            pre::RabbitFrame = 6;
            pre::BoarFrame = 6;
            break;
        }
        case 2 :
        {
            pre::SlimeFrame = 8;
            pre::RabbitFrame = 8;
            pre::BoarFrame = 8;
            break;
        }
    }
    Map.SetMap();
    player.SetUp();
    wave.SetUp("./asset/Enemy/Wave.txt");
    TimeManager::Instance()->reset();

//    screen PauseMenu
    PauseMenu.texture = pre::PauseMenu;

//    Button pause;
    Pause.texture = pre::Pause;
    SDL_QueryTexture(Pause.texture, nullptr, nullptr, &Pause.rectst.w, &Pause.rectst.h);
    Pause.rect = {SCREEN_WIDTH-20-Pause.rectst.w, 20, Pause.rectst.w, Pause.rectst.h};

//    Button resume;
    Resume.texture = pre::Resume;
    SDL_QueryTexture(Resume.texture, nullptr, nullptr, &Resume.rectst.w, &Resume.rectst.h);
    Resume.rect = {370, 421, 196, 66};

//    Button Home;
    Home.texture = pre::Home;
    SDL_QueryTexture(Home.texture, nullptr, nullptr, &Home.rectst.w, &Home.rectst.h);
    Home.rect = {577, 422, 63, 62};

//    Button TickBox
    TickBox.texture = pre::TickBoxTexture;
    SDL_QueryTexture(TickBox.texture, nullptr, nullptr, &TickBox.rectst.w, &TickBox.rectst.h);
    TickBox.rect = {596, 278, 38, 37};
    TickBox.status = 1 - DmgAppear;
//    Sound Control
    SoundEFVolume.texture = pre::SoundEFVoloumeTexture;
    SDL_QueryTexture(SoundEFVolume.texture, nullptr, nullptr, &SoundEFVolume.rectst.w, &SoundEFVolume.rectst.h);
    SoundEFVolume.rect = {389, 160, 225*SoundEFPer, 18};

    SoundEFPoint.texture = pre::SoundEFPointTexture;
    SDL_QueryTexture(SoundEFPoint.texture, nullptr, nullptr, &SoundEFPoint.rectst.w, &SoundEFPoint.rectst.h);
    SoundEFPoint.limit = {387, 0, 217, 0};
    SoundEFPoint.rect = {SoundEFPoint.limit.x+SoundEFPoint.limit.w*SoundEFPer, 230-82, SoundEFPoint.rectst.w, SoundEFPoint.rectst.h };

    MusicVolume.texture = pre::MusicVoloumeTexture;
    SDL_QueryTexture(MusicVolume.texture, nullptr, nullptr, &MusicVolume.rectst.w, &MusicVolume.rectst.h);
    MusicVolume.rect = {389, 242, 225*MusicPer, 18};

    MusicPoint.texture = pre::MusicPointTexture;
    SDL_QueryTexture(MusicPoint.texture, nullptr, nullptr, &MusicPoint.rectst.w, &MusicPoint.rectst.h);
    MusicPoint.limit = {387, 0, 217, 0};
    MusicPoint.rect = {MusicPoint.limit.x+MusicPoint.limit.w*MusicPer, 230, MusicPoint.rectst.w, MusicPoint.rectst.h };

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

    timecount.color = (MapTerrain == 1 ? White : Black);
    killcount.color = (MapTerrain == 1 ? White : Black);
}

void Game::MoveAll()
{
    double a_x, a_y;
    player.Move( a_x, a_y );
    Map.MapMove( -a_x, -a_y );
    for( auto &enemy : enemies ) {
        enemy.ChangeOccupy( -a_x, -a_y, enemies );
        enemy.SetOccupy();

    }
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
    if(wave.WaveNum < 5){
        if( wave.WaveNum > CurrentWave.second )
            CurrentWave.first += wave.GetAmount(), CurrentWave.second = wave.WaveNum;
        //test
//        CurrentWave.first = 1;
        //test
        if( int(SDL_GetTicks()) - timeSpawn.first > timeSpawn.second && enemies.size() < CurrentWave.first ){
            int number = func::random( 1, 10 );
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
            }
        }
        if( player.GetPower( 2 ) && zone.CanDmg == 1 ){
            if( zone.DOT( enemy ) )
            {
                Dmg dmg( zone.damage, enemy.rect.x, enemy.rect.y );
                dmgs.push_back( dmg );
            }
        }

        if(enemy.exist == true && base::CanChoose == true && enemy.RectOccupy.checkRect( player.Body ) ){
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
            if( KameDmg != -1 )
            {
                Dmg dmg( enemy.HP, enemy.rect.x, enemy.rect.y );
                dmgs.push_back( dmg );
                enemy.HP = 0;
                enemy.exist = false;
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
        if(boss.exist == true && base::CanChoose == true && func::checkRect(bossRect, player.Body )  ){
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
            if( KameDmg > 0 )
            {
                boss.HP -= KameDmg;
                Dmg dmg( KameDmg, bossRect.x, bossRect.y );
                dmgs.push_back( dmg );
            }
        }
        if( boss.BossType == 2 && boss.kameha.state == 2 && player.phaseState != 2 )
        {
            int KameDmg = boss.kameha.CheckDmg(base::CenterRect);
            if( KameDmg != -1 ){
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

    TickBox.drawTick();
    Resume.drawObj();
    Home.drawObj();
    SoundEFVolume.drawObj();
    MusicVolume.drawObj();

    SoundEFPoint.drawHold();
    MusicPoint.drawHold();
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
            int DropType = func::random(1, 4);
            int percent = func::random(1, 100);
            if( 1 <= percent && percent <= 50 ) DropType = 1;
            if( 51 <= percent && percent <= 80 ) DropType = 2;
            if( 81 <= percent && percent <= 90 ) DropType = 3;
            if( 91 <= percent && percent <= 100 ) DropType = 4;
            switch (DropType)
            {
                case 1 :
                {
                    Exp exp;
                    exp.type = DropType;
                    exp.SetUp(enemy->GetRect().x, enemy->GetRect().y, -DropType);
                    exps.push_back( exp );
                    break;
                }
                case 2 :
                {
                    Exp exp;
                    exp.type = DropType;
                    exp.SetUp(enemy->GetRect().x, enemy->GetRect().y, -DropType);
                    exps.push_back( exp );
                    break;
                }
                case 3 :
                {
                    Exp exp;
                    exp.type = DropType;
                    exp.SetUp(enemy->GetRect().x, enemy->GetRect().y, -DropType);
                    exps.push_back( exp );
                    break;
                }
            }
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

void Game::EndGame()
{
    if( pre::MapTexture == nullptr ) std::cout << "yes\n";
    Mix_HaltChannel(-1);
    base::UpdateData();
    if( GameWin == -1 ){
        return;
    }
    bool GameQuit = false;
    Screen background;
    if( GameWin == true ) background.SetTexture(std::string("./asset/Screen/YOUWIN.png"));
    else background.SetTexture(std::string("./asset/Screen/YOULOSE.png"));
    background.rectst = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    background.rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    while(!GameQuit)
    {
        while(SDL_PollEvent(&base::g_event))
        {
            if( base::g_event.type == SDL_QUIT){GameQuit = Quit = true;break;}
            if( base::g_event.type == SDL_KEYDOWN && base::g_event.key.keysym.sym == SDLK_RETURN)
            {
                GameQuit = 1;
                break;
            }

        }
        RenderGamePlay( 0 );
        background.drawObj();
        SDL_RenderPresent(base::renderer);
    }
    SDL_RenderClear(base::renderer);
    return ;
}

