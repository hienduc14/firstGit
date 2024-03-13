#include "Game.hpp"

void play::Game( int StartPower ){
    // ve map
    Screen Map;
    Map.rectst = {0, 0, MapWidth*3, MapHeight*3};
    Map.rect = {-MapWidth, -MapHeight, MapWidth*3, MapHeight*3};
    Map.SetTexture(MapImg);
    Map.SetL();
    Player player;
    std::list<Enemy> enemies;
    std::list<Power> powers;
    std::list<Exp> exps;
    int frame = 0;
    double TimeStep = 1000/FPS;
    player.SetPower(StartPower);
    bool quit = false;
    while(!quit)
    {
        TimeManager::Instance()->process();
        int currentTime = SDL_GetTicks();
        while(SDL_PollEvent(&base::g_event))
        {
            if (base::g_event.type == SDL_QUIT)
            {
                quit = true;
                break;
            }

        }

        // nhap thao tac tu ban phim
        player.ResetInput();
        player.KeyInput();
        if( !player.GetPower(0) )player.SetPower(0);

        // random sinh quai
        if( frame%int(FPS*2) == 0 && enemies.size() < 50 ){
            Enemy enemy;
            if( (func::random( 0, 1 )) ) enemy.SetUp( (func::random(0, SCREEN_WIDTH)), 0, SlimeImg );
            else enemy.SetUp( 0, (func::random(0, SCREEN_HEIGHT) ), SlimeImg );
            enemies.push_back( enemy );
        }

        // xu ly dan (neu co)
        if( frame%int(FPS*player.GetCycle(0)) == 0 && player.GetPower(0) ){
            Orb orb;
            orb.Create();
            orb.Start( player.GetDir(), PlayerWidth/2+3*dx[player.GetDir()], PlayerHeight/2+3*dy[player.GetDir()] );
            powers.push_back( orb );
        }

        //xu ly move cac Obj
        player.Move(Map, enemies, powers, exps );

        //cac obj move
        for( auto &enemy : enemies) {
            enemy.Chase();
        }
        for( auto &power : powers ) power.Run();


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
            for( auto &power : powers )
                {
                if( func::checkRect( power.GetRect(), enemy.GetRect() ) )
                {
                    power.exist = 0;
                    enemy.HP -= power.damage;
                    power.SetTexture(std::string("orb_explode.png"));
                }
            }
            if(enemy.exist == true && func::checkRect( player.GetRect(), enemy.GetRect() ) ){
                if(enemy.CoolDown == 0) {
                    player.HP -= enemy.damage;
                    if( player.HP <= 0 ) break;
                    enemy.CoolDown = EnemyCD;
                }
                else enemy.CoolDown -= TimeStep;
            }
        }
        if( player.HP <= 0 ) break;

        for( auto &power : powers ) {
            power.ExistTime -= TimeStep;
            if( power.ExistTime <= 0 ){
                power.exist = 0;
                power.SetTexture(std::string("orb_explode.png"));
            }
        }

        // render
        Map.drawObj();
        for( auto &power : powers ) power.drawObj();
        for( auto &exp : exps ) exp.drawObj();
        player.drawObj();
        for( auto &enemy : enemies) enemy.drawObj();

        SDL_RenderPresent(base::renderer);
        SDL_RenderClear(base::renderer);
        //xoa quai va dan
        auto it = powers.begin();
        while (it != powers.end()) {
            if (it->exist <= 0) it = powers.erase(it);
            else ++it;
        }
        auto its = enemies.begin();
        while (its!= enemies.end()){
            if(its->HP <= 0) {
                Exp exp;
                exp.SetUp(its->GetRect().x, its->GetRect().y, ExpImg);
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

    if( player.HP <= 0 ){
        Map.SetRect(-1000, -1000);
        Map.SetTexture(std::string("GameOver.png"));
        Map.drawObj();
        SDL_RenderPresent(base::renderer);
    }
//    SDL_Delay(5000);
    return ;
}
