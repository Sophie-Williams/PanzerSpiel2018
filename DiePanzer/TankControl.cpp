#include "stdafx.h"
#include "TankControl.h"
#define _USE_MATH_DEFINES
#include <math.h>

void TankControl::Reload() {
	//TODO: create projectile-object
}

/**
 *
**/
void TankControl::Shoot() {
	//TODO: create projectile-object
}

/** @brief	sets speed of the next move and apllies limits
 *	@desc	checks if the requested speed is within the limits set by acceleration_max and decceleration_max. Sets the speed for the next move to the targeted speed (if posible) or to the maximum/minimum achievable value.
 *	@param [in] speed	target speed in maptiles/tick
 *	@return	actual new speed
**/
float TankControl::Set_speed(float speed) {
	float speed_delta = speed - tank->speed;
	if (speed_delta > acceleration_max) {
		speed_delta = acceleration_max;
	}
	else if (speed_delta < decceleration_max) {
		speed_delta = decceleration_max;	//decceleration_max is already negative
	}

	tank->nextMove.acceleration = speed_delta;

	return tank->speed + speed_delta;
}

float TankControl::Set_chassis_rotation(float rotation) {
	float rotation_max = 2 * M_PI / (centrifugal_acceleration_max*tank->speed);

	if (rotation > rotation_max) {
		rotation = rotation_max;
	}
	else if (rotation < -rotation_max) {
		rotation = -rotation_max;
	}
	tank->nextMove.chassis_rotation = rotation;
	return rotation;
}

float TankControl::Set_turret_rotation(float rotation) {
	if (rotation > turret_rotation_max) {
		rotation = turret_rotation_max;
	}
	else if (rotation < (-turret_rotation_max)) {
		rotation = -turret_rotation_max;
	}
	tank->nextMove.turret_rotation = rotation;
	return rotation;
}
void TankControl::Set_tick(uint_fast32_t tick) {
	tank->nextMove.tick = tick;
}