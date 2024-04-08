#pragma once
#include "Func.hpp"
#include <fstream>

class Wave
{
public :
    int per[15][10];
    int amount[10];
    int WaveNum = 0;
    int MaxWave = 10;
    int WaveDis = 10;
public :
    Wave();
    void SetUp(std::string filePath);
    ~Wave();
    void SetWave(int minute, int second);
    int GetEnemy();
    int GetAmount();
};
