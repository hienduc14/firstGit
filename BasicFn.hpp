#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <list>

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;
const int CENTER_X = SCREEN_WIDTH/2;
const int CENTER_Y = SCREEN_HEIGHT/2;

const int dx[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
const int dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
//const char* rival[6] = { "slime_walk.png" };
//const int rival_w[6] = { 220 };
//const int rival_h[6] = { 150 };

namespace base
{
    extern SDL_Window *window;
    extern SDL_Renderer *renderer;
    extern SDL_Event g_event;
    void initSDL();
    void quitSDL();
    SDL_Texture *Load_Image( const char* filePath );
}
