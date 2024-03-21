#include "PowerUp.hpp"


void OrbAdd( std::list<Orb> &orbs, int level, int dir )
{
    int x = CENTER_X, y = CENTER_Y;
    switch (level)
    {
    case 1:
        {
            Orb orb;
            orb.Create();
            orb.Start( dir, x+10*dx[dir], y+10*dy[dir] );
            orbs.push_back( orb );
            break;
        }
    case 2:
        {
            int cDir = (dir-2+8)%8;
            for( int i = 1; i <= 2; i++ ){
                int u = x + 15*dx[cDir], v = y + 15*dy[cDir];
                Orb orb;
                orb.Create();
                orb.Start( dir, u + 10*dx[dir], v + 10*dy[dir] );
                orbs.push_back( orb );
                cDir = (cDir + 4)%8;
            }
            break;
        }
    case 3:
        {
            double addTime = 0;
            for(int u = 1; u <= 2; u++)
            {
                int cDir = (dir-2+8)%8;
                double can = 1;
                if(cDir%2) can = 1.414;
                for( int i = 1; i <= 2; i++ ){
                    int u = x + 15*dx[cDir], v = y + 15*dy[cDir];
                    Orb orb;
                    orb.delayTime = addTime;
                    orb.Create();
                    orb.Start( dir, u + double(10*dx[dir])/can, v + double(10*dy[dir])/can );
                    orbs.push_back( orb );
                    cDir = (cDir + 4)%8;
                }
                addTime+=100;
            }
            break;
        }
    case 4:
        {
            double addTime = 0;
            for(int u = 1; u <= 2; u++)
            {
                int cDir = (dir-2+8)%8;
                for( int i = 1; i <= 2; i++ ){
                    int u = x + 15*dx[cDir], v = y + 15*dy[cDir];
                    Orb orb;
                    orb.delayTime = addTime;
                    orb.Create();
                    orb.Start( dir, u + 10*dx[dir], v + 10*dy[dir] );
                    orbs.push_back( orb );
                    cDir = (cDir + 4)%8;
                }
                cDir = (dir-1+8)%8;
                for( int i = 1; i <= 2; i++ ){
                    int u = x, v = y;
                    Orb orb;
                    orb.delayTime = addTime;
                    orb.Create();
                    orb.Start( cDir, u + 10*dx[cDir], v + 10*dy[cDir] );
                    orbs.push_back( orb );
                    cDir = (cDir + 2)%8;
                }

                addTime+=100;
            }
            break;
        }
    }
}

void FireBallAdd( std::list<FireBall> &fireBalls, Player &player, int f_x, int f_y )
{
    int x = CENTER_X, y = CENTER_Y;
    int dis = 15;
    switch ( player.MyPower[1] )
    {
        case 1:
        {
            FireBall fireBall;
            fireBall.Create();
            fireBall.Start(x, y, f_x, f_y);
            fireBalls.push_back( fireBall );
            player.SetStartCD(1);
            break;
        }
        case 2:
        {
            for(int i = 1; i <= 2; i++){
                FireBall fireBall;
//                fireBall.delayTime = add;
                fireBall.Create();
                fireBall.Start(x+(i-1)*dis, y+(i-1)*dis, f_x, f_y);
                fireBalls.push_back( fireBall );
//                add += 600;
            }
            player.SetStartCD(1);
            break;
        }
        case 3:
        {
            for(int i = 1; i <= 3; i++){
                FireBall fireBall;
//                fireBall.delayTime = add;
                fireBall.v_Obj = 4*FireBallV;
                fireBall.Create();
                fireBall.Start(x+(i-2)*dis, y+(i-2)*dis, f_x, f_y);
                fireBalls.push_back( fireBall );
//                add += 600;
            }
            player.SetStartCD(1);
            break;
        }
        case 4:
        {
            for(int i = 1; i <= 3; i++){
                FireBall fireBall;
//                fireBall.delayTime = add;
                fireBall.v_Obj = 4*FireBallV;
                fireBall.damage *=1.1;
                fireBall.Create();
                fireBall.Start(x+(i-2)*dis, y+(i-2)*dis, f_x, f_y);
                fireBalls.push_back( fireBall );
//                add += 600;
            }
            player.SetStartCD(1);
            player.CD[1] = FireBallCD/2;
            break;
        }
    }
}

void ZoneAdd(Zone &zone, Player &player)
{
    if( zone.CurrentLevel == player.MyPower[2] ) return;
    switch (player.MyPower[2])
    {
        case 1:
        {
            zone.Start();
            break;
        }
        case 2:
        {
            zone.damage = ZoneDmg*2;
            break;
        }
        case 3:
        {
            zone.damage = ZoneDmg+0.05;
            zone.radius = ZoneR+30;
            zone.rect.w = zone.radius*2;
            zone.rect.h = zone.radius*2;
            zone.SetRect(CENTER_X-zone.rect.w/2, CENTER_Y-zone.rect.h/2);
            zone.Located();
            zone.SetL();
            break;
        }
        case 4:
        {
            zone.damage = ZoneDmg*2;
            break;
        }
    }
    zone.CurrentLevel == player.MyPower[2];
}
