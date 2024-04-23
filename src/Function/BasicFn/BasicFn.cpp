#include "BasicFn.hpp"
int GameSpeed = 1;
bool Quit = false;
bool Dot[2001][2001];

void SetDot(int x, int y, int tt)
{
    if( x < 0 || x > SCREEN_WIDTH ) return;
    if( y < 0 || y > SCREEN_HEIGHT ) return;
    Dot[x][y] = tt;
}

bool GetDot(int x, int y)
{
    if( x < 0 || x > SCREEN_WIDTH ) return 0;
    if( y < 0 || y > SCREEN_HEIGHT ) return 0;
    return Dot[x][y];
}
namespace base
{
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Event g_event;

    SDL_Rect CenterRect;
    bool CanChoose = true;
//    int GameSpeed = 1;
    // Các hàm và mã khác...
}

void base::initSDL()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1) SDL_Quit();
    TTF_Init();
    //tao window
    base::window =  SDL_CreateWindow(
                    "Giao dien",
                    SDL_WINDOWPOS_CENTERED,
                    SDL_WINDOWPOS_CENTERED,
                    SCREEN_WIDTH,
                    SCREEN_HEIGHT,
                    SDL_WINDOW_SHOWN
                    );

    if(base::window == nullptr) SDL_Quit();

    //tao renderer
    base::renderer = SDL_CreateRenderer(base::window, -1, SDL_RENDERER_ACCELERATED);
    if(base::renderer == nullptr) SDL_Quit();

    //tao music
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}


void base::quitSDL()
{
    //destroy cac bien roi quit
    SDL_DestroyRenderer(base::renderer);
    SDL_DestroyWindow(base::window);
    TTF_Quit();
    SDL_Quit();
}

SDL_Texture *base::Load_Image( const std::string filePath )
{
    SDL_Texture *screen = nullptr;
    screen = IMG_LoadTexture(base::renderer, filePath.c_str());
	return screen;
};

SDL_Texture *base::Load_Text( const std::string text, TTF_Font *font, SDL_Color TextColor )
{
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), TextColor);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(base::renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}
