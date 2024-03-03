#include <iostream>
#include <SDL.h>
using namespace std;

int main( int argc, char* args[] )
{
    SDL_Window* newWindow = NULL;
    SDL_Surface* newSurface = NULL;
    newWindow = SDL_CreateWindow( "Yeah!!!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 600, SDL_WINDOW_SHOWN );
    SDL_Delay( 5000 );
}
