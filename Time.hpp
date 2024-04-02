#pragma once
#include "BasicFn.hpp"

class TimeManager
{
    uint64_t current, last, elapse;
    double elapsedTime;
    double FPS;
    static TimeManager *instance;
public:
    TimeManager();
    ~TimeManager();

    static TimeManager *Instance() {
        if (instance == nullptr) instance = new TimeManager();
        return instance;
    }
    double getFPS() const {
        return FPS;
    }
    double getElapsedTime() const {
        return elapsedTime;
    }

    void process();

    void reset();

};
