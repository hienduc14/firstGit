#include "Wave.hpp"

Wave::Wave()
{

}


void Wave::SetUp(std::string filePath)
{
    std::fstream fin;
    fin.open(filePath);
//    memset(per, 0, sizeof(per));
    for(int i = 0; i < 10; i++)
        for(int j =0; j < 5; j++) fin >> per[i][j];
    fin.close();
}

Wave::~Wave()
{

}

void Wave::SetWave(int minute, int second)
{
    int dis = 10;
    WaveNum = minute*(60/dis);
    WaveNum += second/dis;
}

int Wave::GetEnemy()
{
    int u = func::random(1, 100);

    std::cout << u << '\n';

    for(int i = 0; i < 5; i++)
        if( u <= per[WaveNum][i] ){
            if( per[WaveNum][i] ) return i;
        }
        else u -= per[WaveNum][i];
    return 0;
}
