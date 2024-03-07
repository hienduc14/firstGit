#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;

namespace base
{
    extern SDL_Window *window;
    extern SDL_Renderer *renderer;
    extern SDL_Event g_event;
    void initSDL();
    void quitSDL();
    SDL_Texture *Load_Image( const char* filePath );
}
