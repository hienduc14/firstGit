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

//        // xoa dan
//        for( auto &power : powers ) if(  )

        // random sinh quai
        if( ok == 10 ){
            Enemy enemy;
            if( (func::random( 0, 1 )) ) enemy.SetUp( (func::random(0, SCREEN_WIDTH)), 0 );
            else enemy.SetUp( 0, (func::random(0, SCREEN_HEIGHT) ));
            enemies.push_back( enemy );
            ok = 0;
        }
        // xu ly dan (neu co)
        if( ok == 5 ){
            Power gun;
            gun.SetType(0);
            gun.Start( player.GetDir(), PlayerWidth/2+3*dx[player.GetDir()], PlayerHeight/2+3*dy[player.GetDir()] );
            powers.push_back( gun );
        }
        ok++;
        //xu ly move cac Obj
        player.Move(BackGr, enemies, powers );

        //cac obj move
        for( auto &enemy : enemies) enemy.Chase();
        for( auto &power : powers ) power.Run();

        // kiem tra va cham
        for( auto &enemy : enemies )
        {
            for( auto &power : powers )
                {
                if( func::checkRect( power.GetRect(), enemy.GetRect() ) )
                {
                    power.exist = 0;
                    enemy.exist = 0;
                    const char* x = "orb_explode.png";
                    power.SetTexture(x);
                }
            }
        }
        // render
        BackGr.drawObj();
        player.drawObj();
        for( auto &enemy : enemies)enemy.drawObj();
        for( auto power : powers ) power.drawObj();

        SDL_RenderPresent(base::renderer);

        //xoa quai va dan
        for( auto &enemy : enemies)enemy.drawObj();
        for( auto power : powers ) power.drawObj();
        auto it = enemies.begin();
        while (it != enemies.end()) {
            if (it->exist == 0) it = enemies.erase(it);
            else ++it;
        }
        auto its = powers.begin();
        while (its!= powers.end()){
            if(its->exist == 0) its = powers.erase(its);
            else ++its;
        }
        SDL_Delay( 50 );
    }


    SDL_Delay( 50000 );

    // thoat chuong trinh
    base::quitSDL();
    return 0;
}
