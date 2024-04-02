#pragma once
#include "Func.hpp"
#include <fstream>

class Wave
{
public :
    int per[15][10];
    int WaveNum = 0;
public :
    Wave();
    void SetUp(std::string filePath);
    ~Wave();
    void SetWave(int minute, int second);
    int GetEnemy();
};
