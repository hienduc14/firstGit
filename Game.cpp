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

void Game::play( int StartPower ){
//    std::cout << "........................" << '\n';
//    std::cout << enemies.size() << '\n';
    Prepare();
//    SDL_Delay(5000);
//    player.MyPower[0] = 4;
//    player.MyPower[1] = 4;
//    player.MyPower[2] = 1;
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
                    pause.CheckMouse(base::g_event);
                    if(pause.status == 1) GameState = 1;
                    break;
                case 1 :
                    home.CheckMouse(base::g_event);
                    if(home.status == 1){GameQuit = true; break;}
                    resume.CheckMouse(base::g_event);
                    if(resume.status == 1){GameState = 0;}
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
            player.Move(Map, enemies, orbs, fireBalls, exps );

            //cac obj move
            for( auto &enemy : enemies) enemy.MoveOccupy( enemies );

            for( auto &orb : orbs )
                if( orb.delayTime <= 0 ) orb.Run();
                else orb.delayTime -= TimeStep;
            for( auto &fireBall : fireBalls )
                if( fireBall.delayTime <= 0 ) fireBall.Run();
                else fireBall.delayTime -= TimeStep;

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

    if( player.HP <= 0 ){
        Screen GameOver;
        GameOver.SetTexture(std::string("GameOver.png"));
        GameOver.drawObj();
        SDL_RenderPresent(base::renderer);
        SDL_Delay(5000);
    }
    return ;
}

void Game::Prepare()
{
    LoadAll preload;
    preload.loading();
//    ve map
//    Screen Map;
    Map.rectst = {0, 0, MapWidth*3, MapHeight*3};
    Map.rect = {-MapWidth, -MapHeight, MapWidth*3, MapHeight*3};
    Map.texture = pre::MapTexture;
    Map.SetL();

//    Button pause;
    pause.texture = base::Load_Image(PauseImg);
    pause.rectst = {0, 0, 131, 116};
    pause.rect = {SCREEN_WIDTH-80,0, 80, 80};

//    Button resume;
    resume.texture = base::Load_Image(ResumeImg);
    resume.rectst = {0, 0, 401, 102};
    resume.rect = {CENTER_X+300-200-20, CENTER_Y+250-50-20, 200, 50};

//    Button home;
    home.texture = base::Load_Image(HomeImg);
    home.rectst = {0, 0, 131, 116};
    home.rect = {CENTER_X+300-200-60-20,CENTER_Y+250-50-20, 50, 50};

//    Screen PauseMenu;
    PauseMenu.texture = base::Load_Image(PauseMenuImg);
    PauseMenu.rectst = {0, 0, 624, 480};
    PauseMenu.rect = {CENTER_X-300, CENTER_Y-250, 600, 500};

    player.SetUp();
    wave.SetUp("Wave.txt");
    TimeManager::Instance()->reset();
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
    if( int(SDL_GetTicks()) - timeSpawn.first > timeSpawn.second && enemies.size() < 50 ){
        int number = func::random( 1, 5 );
        for( int i = 1; i <= number; i++ ){
            for( int j = 1; j <= 10; j++ ){
                Enemy enemy;
                int type = wave.GetEnemy();
                std::cout << wave.WaveNum << " " << type << '\n';
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

        if(enemy.exist == true && enemy.RectOccupy.checkRect( player.GetRect() ) ){
            if(enemy.CoolDown == EnemyCD ) {
                player.Bleeding(enemy.damage);
                if( player.HP <= 0 ) break;
            }
            enemy.CoolDown -= TimeStep;
            if(enemy.CoolDown <= 0 ) enemy.CoolDown = EnemyCD;
        }
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
    player.renderPlayer();
//    for( auto &enemy : enemies) enemy.drawObj();
    for( auto &enemy : enemies) enemy.RenderMoving( IsMoving, 1, 0 );
    for( auto &dmg : dmgs ) dmg.PopUp(IsMoving);
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


