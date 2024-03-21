#pragma once
#include "Orb.hpp"
#include "FireBall.hpp"
#include "Zone.hpp"
#include "Player.hpp"

void OrbAdd( std::list<Orb> &orbs, int level, int dir );

void FireBallAdd( std::list<FireBall> &fireBalls, Player &player, int f_x, int f_y );

void ZoneAdd(Zone &zone, Player &player);
