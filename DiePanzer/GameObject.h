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

protected:
	Vector2 coordinates;	///element 0: x, element 1: y
	uint32_t id;
	uint32_t faction;
public:
	virtual ClassID Get_type() = 0;

};