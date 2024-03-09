#include <SDL.h>
#include "BasicFn.hpp"
#include "Func.hpp"
#include "BigObj.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "Enemy.hpp"
#include "Power.hpp"
int main( int argc, char* args[] )
{
    // khoi tao window, renderer...
    base::initSDL();

    // ve map
    std::string x = "map.jpg";

    Map BackGr;
    Player player;
    std::list<Enemy> enemies;
    std::list<Power> powers;
    int ok = 0;

    bool quit = false;
    while(!quit)
    {
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

        // xu ly dan (neu co)
        if( ok == 5 ){
            Power gun;
            gun.SetType(0);
            gun.Start( player.GetDir(), PlayerWidth/2+3*dx[player.GetDir()], PlayerHeight/2+3*dy[player.GetDir()] );
            powers.push_back( gun );
        }
        // random sinh quai
        if( ok == 10 ){
            Enemy enemy;
            if( (func::random( 0, 1 )) ) enemy.SetUp( (func::random(0, SCREEN_WIDTH)), 0 );
            else enemy.SetUp( 0, (func::random(0, SCREEN_HEIGHT) ));
            enemies.push_back( enemy );
            ok = 0;
        }
        ok += 1;

        //xu ly move cac Obj
        player.Move(BackGr, enemies, powers );

        //cac obj move
        for( auto &enemy : enemies) enemy.Chase();
        for( auto &power : powers ) power.Run();

        // render
        BackGr.drawObj();
        player.drawObj();
        for( auto &enemy : enemies)enemy.drawObj();
        for( auto power : powers ) power.drawObj();

        SDL_RenderPresent(base::renderer);
        SDL_Delay( 10 );
    }


    SDL_Delay( 50000 );

    // thoat chuong trinh
    base::quitSDL();
    return 0;
}
