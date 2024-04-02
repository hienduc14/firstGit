#include "Time.hpp"

//.......................TimeManager..............................................
TimeManager *TimeManager::instance = nullptr;
TimeManager::TimeManager()
{
    current = SDL_GetPerformanceCounter();
    last = SDL_GetPerformanceCounter();
    elapse = SDL_GetPerformanceCounter();
    elapsedTime = 0;
}
TimeManager::~TimeManager() {
    instance = nullptr;
}

void TimeManager::process() {
    current = SDL_GetPerformanceCounter();
    elapse = current - last;
    last = current;
    elapsedTime = elapse / double(SDL_GetPerformanceFrequency());
}

void TimeManager::reset()
{
    current = SDL_GetPerformanceCounter();
    last = SDL_GetPerformanceCounter();
    elapse = SDL_GetPerformanceCounter();
    elapsedTime = 0;
}
