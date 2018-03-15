#pragma once
#include <cstdint>
#include "Vector.h"

class GameObject
{
private:
	uint32_t id;
	Vector2 coordinates;
	uint32_t faction;
};