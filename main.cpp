#include <SDL.h>
#include "BasicFn.hpp"
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
    Enemy enemy;
    Power gun;

    gun.SetType(0);
    int ok = 1;
    gun.drawObj();

    enemy.SetUp();
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
        if( ok == 1 ){
            gun.Start( player.GetDir(), PlayerWidth/2+3*dx[player.GetDir()], PlayerHeight/2+3*dy[player.GetDir()] );
            ok = 0;
        }

        //xu ly move cac Obj
        player.Move(BackGr, enemy, gun);

        //cac obj move
        gun.Run();
        enemy.Chase();

        BackGr.drawObj();
        player.drawObj();
        enemy.drawObj();
        gun.drawObj();

        SDL_RenderPresent(base::renderer);
        SDL_Delay( 50 );
    }


    SDL_Delay( 50000 );

    // thoat chuong trinh
    base::quitSDL();
    return 0;
}
