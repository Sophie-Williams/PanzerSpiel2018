#pragma once
#include <cstdint>
#include "GameObject.h"


class Tank : public GameObject
{
private:
	float cannon_orientation;
	float chassis_orientation;
	float speed;
	uint32_t ammo;
	bool cannon_loaded;
	uint32_t remaining_reload_time;
};