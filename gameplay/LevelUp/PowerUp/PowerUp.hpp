#pragma once
#include "../../Power/Orb/Orb.hpp"
#include "../../Power/FireBall/FireBall.hpp"
#include "../../Power/Zone/Zone.hpp"
#include "../../Player/Player.hpp"

void OrbAdd( std::list<Orb> &orbs, int level, int dir );

void FireBallAdd( std::list<FireBall> &fireBalls, Player &player, int f_x, int f_y );

void ZoneAdd(Zone &zone, Player &player);
