#include "MovingObj.hpp"

MovingObj :: MovingObj()
{
}

MovingObj :: ~MovingObj()
{

}

void MovingObj::Change( double ax, double ay )
{
//    std::cout << "---------------\n";
//    std::cout << L_x << " " << L_y << " " << ax << " " << ay << '\n';\

    L_x += ax*TimeManager::Instance()->getElapsedTime();
    L_y += ay*TimeManager::Instance()->getElapsedTime();
    rect.x = L_x; rect.y = L_y;
//    std::cout << L_x << " " << L_y <<  '\n';
//    std::cout << rect.x << " " << rect.y << '\n';
    Located();
}

void MovingObj::Located(){
    c_x = rect.x + rect.w/2;
    c_y = rect.y + rect.h/2;
}
