#include <SDL.h>
#include "BasicFn.hpp"
#include "BigObj.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "Enemy.hpp"
int main( int argc, char* args[] )
{
    // khoi tao window, renderer...
    base::initSDL();

    // ve map
    std::string x = "map.jpg";

    Map BackGr;
    Player player;
    Enemy enemy;
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
        player.ResetInput();
        player.KeyInput();
        player.Move(BackGr, enemy);
        enemy.Chase();
        BackGr.drawObj();
        player.drawObj();
        enemy.drawObj();
//        std::vector<Ammo*> ammoList = player.GetAmmoList();
//        std::vector<Ammo*> &ammoList = player.AmmoList;
//        for (auto it = player.AmmoList.begin(); it != player.AmmoList.end(); ) {
//            Ammo *u = (*it);
//            if ( u->GetIsMove() == false) {
//                std::cout << "A";
//                it = player.AmmoList.erase(it); // Xoá phần tử
//            } else {
//                ++it;
//            }
//        }
//        for( Ammo* ammo : player.AmmoList ){
//            if( ammo != NULL ){
//                if( ammo->GetIsMove() == true ){
//                    ammo->drawObj();
//                    ammo->Move(player.GetDir(), 1, ammo->GetRect());
//                }
//
//            }
//
//        }

        SDL_RenderPresent(base::renderer);
        SDL_Delay( 10 );
    }


    SDL_Delay( 50000 );

    // thoat chuong trinh
    base::quitSDL();
    return 0;
}
