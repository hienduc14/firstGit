#include <SDL.h>
#include "BasicFn.hpp"
#include "Func.hpp"
#include "BigObj.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "Enemy.hpp"
#include "Power.hpp"
#include "Orb.hpp"
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

    int frame = 0;
    bool quit = false;
    while(!quit)
    {
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
        if( frame%(FPS*2) == 0 && enemies.size() < 50 ){
            Enemy enemy;
            if( (func::random( 0, 1 )) ) enemy.SetUp( (func::random(0, SCREEN_WIDTH)), 0 );
            else enemy.SetUp( 0, (func::random(0, SCREEN_HEIGHT) ));
            enemies.push_back( enemy );
        }
        // xu ly dan (neu co)
        if( frame%(FPS*player.GetCycle(0)) == 0 && player.GetPower(0) ){
            Orb orb;
            orb.Create();
            orb.Start( player.GetDir(), PlayerWidth/2+3*dx[player.GetDir()], PlayerHeight/2+3*dy[player.GetDir()] );
            powers.push_back( orb );
        }
        //xu ly move cac Obj
        player.Move(BackGr, enemies, powers );

        //cac obj move
        for( auto &enemy : enemies) {
            enemy.Chase();
        }
        for( auto &power : powers ) power.Run();

        // kiem tra va cham
        for( auto &enemy : enemies )
        {
            for( auto &power : powers )
                {
                if( func::checkRect( power.GetRect(), enemy.GetRect() ) )
                {
                    power.exist = 0;
                    enemy.HP -= power.damage;
                    const char* x = "orb_explode.png";
                    power.SetTexture(x);
                }
            }
            if(enemy.exist == true && func::checkRect( player.GetRect(), enemy.GetRect() ) ){
                if(enemy.CoolDown == 0) {
                    player.HP -= enemy.damage;
                    if( player.HP <= 0 ) break;
                    enemy.CoolDown = 2;
                }
                else enemy.CoolDown --;
            }
        }
        if( player.HP <= 0 ) break;

        // render
        BackGr.drawObj();
        for( auto &power : powers ) power.drawObj();
        player.drawObj();
        for( auto &enemy : enemies) enemy.drawObj();

        SDL_RenderPresent(base::renderer);

        //xoa quai va dan
        auto it = enemies.begin();
        while (it != enemies.end()) {
            if (it->HP <= 0) it = enemies.erase(it);
            else ++it;
        }
        auto its = powers.begin();
        while (its!= powers.end()){
            if(its->exist == 0) its = powers.erase(its);
            else ++its;
        }

        int frameTime = SDL_GetTicks() - currentTime;
//        std::cout << frameTime << '\n';
        if( frameTime < 1000/FPS ) SDL_Delay( 1000/FPS-frameTime );
        frame++;
//        break;
    }

    if( player.HP <= 0 ){
        BackGr.SetRect(-1000, -1000);
        BackGr.SetTexture(std::string("GameOver.png"));
        BackGr.drawObj();
        SDL_RenderPresent(base::renderer);
    }
    SDL_Delay( 10000 );

    // thoat chuong trinh
    base::quitSDL();
    return 0;
}
