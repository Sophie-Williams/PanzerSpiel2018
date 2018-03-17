#pragma once
#include <cstdint>
#include "GameObject.h"
#include "Move.h"
#include "TankControl.h"
#include "World.h"

class Tank : public GameObject 
{
	friend class World;
	friend class Tankcontrol;

private:
	float turret_orientation;	///0..2pi; 0 is forward in relation to the chassis; clockwise
	float chassis_orientation;	///0...2pi; 0 is towards the top of the screen; clockwise
	float speed;	///in maptiles/tick
	uint32_t ammo;
	bool cannon_loaded;
	uint32_t remaining_reload_time;
	Move nextMove;

public:
	Move Get_move();
};