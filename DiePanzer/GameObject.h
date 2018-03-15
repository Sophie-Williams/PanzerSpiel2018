#pragma once
#include <cstdint>
#include "Vector.h"

enum class ClassID 
{ 
	tank_standart = 0, 
	bullet_standart 
};

class GameObject
{
private:
	uint32_t id;
	Vector2 coordinates;
	uint32_t faction;
public:
	virtual ClassID Get_type() = 0;
};