#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <list>
#include <string>
#include <cstring>
#include "../../TimeManage/Time.hpp"
const SDL_Color Black = {0, 0, 0, 255};
const SDL_Color White = {255, 255, 255, 255};

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;
const int CENTER_X = SCREEN_WIDTH/2;
const int CENTER_Y = SCREEN_HEIGHT/2;
const double FPS = 60;
const double TimeStep = 1000/FPS;
const int dx[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
const int dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
extern int GameSpeed;
extern bool Quit;
extern bool DmgAppear;
extern double SoundEFPer;
extern double MusicPer;
extern bool Dot[2001][2001];
void SetDot(int x, int y, int tt);
bool GetDot(int x, int y);

namespace base
{
    extern SDL_Window *window;
    extern SDL_Renderer *renderer;
    extern SDL_Event g_event;
    //player rect de ktra occupy voi enemy
    extern SDL_Rect CenterRect;
    extern bool CanChoose;

    void initSDL();
    void quitSDL();
    SDL_Texture *Load_Image( const std::string filePath );
    SDL_Texture *Load_Text( const std::string text, TTF_Font *font, SDL_Color TextColor );
}
