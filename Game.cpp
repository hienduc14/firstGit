#include "Game.hpp"

Game::Game()
{

}

Game::~Game()
{

}

void Game::play( int StartPower ){
    Prepare();
//    player.SetPower(StartPower);
//    player.SetPower(1);
    player.SetPower(2);

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
            for( auto &enemy : enemies) {
                enemy.Chase();
            }
            for( auto &orb : orbs ) orb.Run();
            for( auto &fireBall : fireBalls ) fireBall.Run();

            //Hap thu kinh nghiem
            for( auto &exp : exps )
                if(exp.exist == true) {
                    Upgrades += player.ExpAbsorb( exp );
                    if( Upgrades ) GameState = 2;
                }

            // kiem tra va cham

            for( auto &enemy : enemies )
            {
                for( auto &orb : orbs )
                    {
                    if( func::checkRect( orb.GetRect(), enemy.GetRect() ) )
                    {
                        orb.exist = 0;
                        enemy.HP -= orb.damage;
                        orb.SetTexture(std::string("orb_explode.png"));
                    }
                }
                for( auto &fireBall : fireBalls )
                    {
                    if( func::checkRect( fireBall.GetRect(), enemy.GetRect() ) )
                    {
                        fireBall.exist = 0;
                        enemy.HP -= fireBall.damage;
                        fireBall.SetTexture(std::string("FireBall_explode.png"));
                    }
                }
                if( player.GetPower( 2 ) ){
                    zone.DOT( enemy );
                }

                if(enemy.exist == true && func::checkRect( player.GetRect(), enemy.GetRect() ) ){

                    if(enemy.CoolDown == EnemyCD ) {
    //                    std::cout << enemy.CoolDown << '\n';
    //                    player.HP -= enemy.damage;
                        player.Bleeding(enemy.damage);
                        if( player.HP <= 0 ) break;
                    }
                    enemy.CoolDown -= TimeStep;
                    if(enemy.CoolDown <= 0 ) enemy.CoolDown = EnemyCD;
                }
            }

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

            // render
            RenderGamePlay( 1 );
            pause.drawObj();

            SDL_RenderPresent(base::renderer);

            SDL_RenderClear(base::renderer);

            if( player.HP <= 0 ) break;
    //        std::cout << player.HP << '\n';

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
    pre::MapTexture = base::Load_Image(MapImg);
    pre::SlimeTexture = base::Load_Image(SlimeImg);
    pre::OrbTexture = base::Load_Image(OrbImg);
    pre::FireBallTexture = base::Load_Image(FireBallImg);
    pre::ZoneTexture = base::Load_Image(ZoneImg);
    pre::ExpTexture = base::Load_Image(ExpImg);
    pre::PlayerTexture = base::Load_Image(PlayerImg);
    pre::HealthTexture = base::Load_Image(HealthImg);
    pre::HealthBarTexture = base::Load_Image(HealthBarImg);
    pre::ExpPointTexture = base::Load_Image(ExpPointImg);
    pre::ExpBarTexture = base::Load_Image(ExpBarImg);
    pre::HPCardTexture = base::Load_Image(HPCardImg);
    pre::WaterBallCardTexture = base::Load_Image(WaterBallCardImg);
    pre::FireBallCardTexture = base::Load_Image(FireBallCardImg);
    if( pre::WaterBallCardTexture== nullptr ) std::cout << "NOOOOOOOOOOOOOOOO" << '\n';
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
}

void Game::LevelUp()
{
    RenderGamePlay( 0 );
    bool xd[4] = {0, 0, 0, 0} ;
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
        Enemy enemy;
        if( (func::random( 0, 1 )) ) enemy.SetUp( (func::random(0, SCREEN_WIDTH)), 0, 1);
        else enemy.SetUp( 0, (func::random(0, SCREEN_HEIGHT) ), 1);
        enemies.push_back( enemy );
        timeSpawn.first = SDL_GetTicks();
    }

}

void Game::Firing()
{
    if( player.GetPower(0) && int(SDL_GetTicks())- player.GetStartCD(0) >= player.GetCD(0)  ){
        Orb orb;
        orb.Create();
        orb.Start( player.GetDir(), PlayerWidth/2+3*dx[player.GetDir()], PlayerHeight/2+3*dy[player.GetDir()] );
        orbs.push_back( orb );
        player.SetStartCD(0);
    }
    if( player.GetPower(1) && int(SDL_GetTicks()) - player.GetStartCD(1) >= player.GetCD(1)  ){
        int f_x = 1e9, f_y = 1e9; double luu = 1e9;
        for(auto &enemy : enemies) if(luu > func::dist(CENTER_X, CENTER_Y, enemy.c_x, enemy.c_y) )
            {
                luu = func::dist(CENTER_X, CENTER_Y, enemy.c_x, enemy.c_y);
                f_x = enemy.c_x; f_y = enemy.c_y;
            }
        if( f_x != 1e9 ){
            FireBall fireBall;
            fireBall.Create();
            fireBall.Start( f_x, f_y );
            fireBalls.push_back( fireBall );
            player.SetStartCD(1);
        }
    }
    if( player.GetPower( 2 ) )
    {
        zone.Start();
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
    for( auto &orb : orbs ) orb.drawObj();
    for( auto &fireBall : fireBalls ) fireBall.RenderMoving( IsMoving );
    zone.drawObj();
    for( auto &exp : exps ) exp.drawObj();
    player.renderPlayer();
    for( auto &enemy : enemies) enemy.drawObj();

}

void Game::RemoveThing()
{
    auto it = orbs.begin();
    while (it != orbs.end()) {
        if (it->exist <= 0) it = orbs.erase(it);
        else ++it;
    }
    auto itk = fireBalls.begin();
    while (itk != fireBalls.end()) {
        if (itk->exist <= 0) itk = fireBalls.erase(itk);
        else ++itk;
    }
    auto its = enemies.begin();
    while (its!= enemies.end()){
        if(its->HP <= 0) {
            Exp exp;
            exp.SetUp(its->GetRect().x, its->GetRect().y, 0);
            exps.push_back( exp );
            its = enemies.erase(its);
        }
        else ++its;
    }
    auto itx = exps.begin();
    while (itx!= exps.end()){
        if(itx->exist == 0) {
            itx = exps.erase(itx);
        }
        else ++itx;
    }
}


