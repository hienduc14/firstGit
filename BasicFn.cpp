#include "BasicFn.hpp"

namespace base
{
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Event g_event;

    // Các hàm và mã khác...
}

void base::initSDL()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1) SDL_Quit();

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
}


void base::quitSDL()
{
    //destroy cac bien roi quit
    SDL_DestroyRenderer(base::renderer);
    SDL_DestroyWindow(base::window);
    SDL_Quit();
}

SDL_Texture *base::Load_Image( std::string &filePath )
{
    SDL_Surface *surface = nullptr;
    SDL_Texture *screen = nullptr;
    // load anh vao surface
    surface = IMG_Load(filePath.c_str());

    if (surface != NULL)
    {
        //gan surface vao texture roi t
	    screen = SDL_CreateTextureFromSurface(base::renderer, surface);
		SDL_FreeSurface(surface);
	}
	return screen;
};
