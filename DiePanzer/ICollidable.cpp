#include "stdafx.h"
#include "ICollidable.h"
#include <cmath>

float ICollidable::get_bounding_radius() {
	return hypot(collision_heigth, collision_width);	//hypotenuse/root square sum of arguments
}