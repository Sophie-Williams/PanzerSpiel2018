#pragma once
#include "Tank.h"
#include <cstdint>

class TankControl
{
private:
	Tank* tank;
	void Reload();

	const float acceleration_max = 20.0f / 60.0f;	///<in maptiles/tick
	const float decceleration_max = -50.0f / 60.0f;	///<in maptiles/tick
	const float centrifugal_acceleration_max = 15.0f / 60.0f;	///<in maptiles/tick
	const float turret_rotation_max = 0.318f;	///< approx. 2s/(2*pi)

public:
	void Shoot();
	float Set_speed(float speed);
	float Set_chassis_rotation(float rotation);
	float Set_turret_rotation(float rotation);
	void Set_tick(uint_fast32_t tick);
};