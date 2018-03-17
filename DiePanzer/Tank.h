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
<<<<<<< HEAD

=======
>>>>>>> f65e168d2b1270ea816c673cd099269d0c000f9c
private:
	float turret_orientation;
	float chassis_orientation;
	float speed;
	uint32_t ammo;
	bool cannon_loaded;
	uint32_t remaining_reload_time;
	Move nextMove;

public:
	Move Get_move();
};