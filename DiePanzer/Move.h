#pragma once

#include <cstdint>
#include "TankControl.h"

class Move {
	friend class TankControl;
private:
	float cannon_rotation;
	float chassis_rotation;
	float acceleration;
	uint_fast32_t tick;
public:
	float get_turret_rotation() { return cannon_rotation; }
	float get_chassis_rotation() { return chassis_rotation; }
	float get_acceleration() { return acceleration; }
	uint_fast32_t get_tick() { return tick; }
};