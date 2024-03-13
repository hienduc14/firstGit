#include "Game.hpp"

void play::Game( int StartPower ){
    pre::MapTexture = base::Load_Image(MapImg);
    pre::SlimeTexture = base::Load_Image(SlimeImg);
    pre::OrbTexture = base::Load_Image(OrbImg);
    pre::ExpTexture = base::Load_Image(ExpImg);
    pre::PlayerTexture = base::Load_Image(PlayerImg);
    pre::HealthTexture = base::Load_Image(HealthImg);
    pre::HealthBarTexture = base::Load_Image(HealthBarImg);
    // ve map
    Screen Map;
    Map.rectst = {0, 0, MapWidth*3, MapHeight*3};
    Map.rect = {-MapWidth, -MapHeight, MapWidth*3, MapHeight*3};
    Map.texture = pre::MapTexture;
    Map.SetL();

    Button pause;
    pause.texture = base::Load_Image(PauseImg);
    pause.rectst = {0, 0, 131, 116};
    pause.rect = {SCREEN_WIDTH-80,0, 80, 80};

    Button resume;
    resume.texture = base::Load_Image(ResumeImg);
    resume.rectst = {0, 0, 401, 102};
    resume.rect = {CENTER_X+300-200-20, CENTER_Y+250-50-20, 200, 50};

    Button home;
    home.texture = base::Load_Image(HomeImg);
    home.rectst = {0, 0, 131, 116};
    home.rect = {CENTER_X+300-200-60-20,CENTER_Y+250-50-20, 50, 50};

    Screen PauseMenu;
    PauseMenu.texture = base::Load_Image(PauseMenuImg);
    PauseMenu.rectst = {0, 0, 624, 480};
    PauseMenu.rect = {CENTER_X-300, CENTER_Y-250, 600, 500};


    Player player;
    std::list<Enemy> enemies;
    std::list<Orb> orbs;
    std::list<Exp> exps;
    int frame = 0;
    player.SetPower(StartPower);

    int GameState = 0;
    bool GameQuit = false;
    while(!GameQuit)
    {
        TimeManager::Instance()->process();
        int currentTime = SDL_GetTicks();


        while(SDL_PollEvent(&base::g_event))
        {
            if (base::g_event.type == SDL_QUIT){GameQuit = Quit = true;break;}
            if(GameState == 0){
                pause.CheckMouse(base::g_event);
                if(pause.status == 1) GameState = 1;
            }
            if(GameState == 1){
                home.CheckMouse(base::g_event);
                if(home.status == 1){GameQuit = true; break;}
                resume.CheckMouse(base::g_event);
                if(resume.status == 1){GameState = 0;}
            }
        }
//        std::cout << pause.status << '\n';
        if(GameState == 1)
        {
            Map.drawObj();
            for( auto &orb : orbs ) orb.drawObj();
            for( auto &exp : exps ) exp.drawObj();
            player.renderPlayer();
            for( auto &enemy : enemies) enemy.drawObj();
            PauseMenu.drawObj();
            resume.drawObj();
            home.drawObj();
            SDL_RenderPresent(base::renderer);
            int frameTime = SDL_GetTicks() - currentTime;
//        std::cout << frameTime << '\n';
            if( frameTime < TimeStep ) SDL_Delay( TimeStep-frameTime );
        }
        if(GameState == 0)
        {
            // nhap thao tac tu ban phim
            player.ResetInput();
            player.KeyInput();
            if( !player.GetPower(0) )player.SetPower(0);

            // random sinh quai
            if( frame%int(FPS*2) == 0 && enemies.size() < 50 ){
                Enemy enemy;
                if( (func::random( 0, 1 )) ) enemy.SetUp( (func::random(0, SCREEN_WIDTH)), 0, 1);
                else enemy.SetUp( 0, (func::random(0, SCREEN_HEIGHT) ), 1);
                enemies.push_back( enemy );
            }

            // xu ly dan (neu co)
            if( frame%int(FPS*player.GetCycle(0)) == 0 && player.GetPower(0) ){
                Orb orb;
                orb.Create();
                orb.Start( player.GetDir(), PlayerWidth/2+3*dx[player.GetDir()], PlayerHeight/2+3*dy[player.GetDir()] );
                orbs.push_back( orb );
            }

            //xu ly move cac Obj
            player.Move(Map, enemies, orbs, exps );

            //cac obj move
            for( auto &enemy : enemies) {
                enemy.Chase();
            }
            for( auto &orb : orbs ) orb.Run();


            for( auto &exp : exps ) {
    //            std::cout << exp.c_x << " " << exp.c_y << '\n';
    //            std::cout << func::dist( exp.c_x, exp.c_y, CENTER_X, CENTER_Y) << '\n';
                if( exp.exist == 1 && func::dist( exp.c_x, exp.c_y, CENTER_X, CENTER_Y) <= 10 ){
                    player.ExpBar += exp.stat;
                    exp.exist = 0;
                    continue;
                }
                if( exp.exist == 1 && func::dist( exp.c_x, exp.c_y, CENTER_X, CENTER_Y) <= PlayerR ) {
                    exp.Chase();
                }

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

            // render
            Map.drawObj();
            for( auto &orb : orbs ) orb.drawObj();
            for( auto &exp : exps ) exp.drawObj();
            player.renderPlayer();
            for( auto &enemy : enemies) enemy.drawObj();
            pause.drawObj();


            SDL_RenderPresent(base::renderer);
            SDL_RenderClear(base::renderer);
            if( player.HP <= 0 ) break;
    //        std::cout << player.HP << '\n';

            //xoa quai va dan
            auto it = orbs.begin();
            while (it != orbs.end()) {
                if (it->exist <= 0) it = orbs.erase(it);
                else ++it;
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
            int frameTime = SDL_GetTicks() - currentTime;
    //        std::cout << frameTime << '\n';
            if( frameTime < TimeStep ) SDL_Delay( TimeStep-frameTime );
            frame++;
    //        break;
        }
    }

    if( player.HP <= 0 ){
        Map.SetRect(-1000, -1000);
        Map.SetTexture(std::string("GameOver.png"));
        Map.drawObj();
        SDL_RenderPresent(base::renderer);
        SDL_Delay(5000);
    }
//    SDL_Delay(1000);
    return ;
}

