#pragma once

/**
 * 
 *
**/
class ICollidable {
protected:
	float collision_width;
	float collision_heigth;
public:
	float get_collision_width() { return collision_width; }	///return: width in maptiles
	float get_collision_heigth() { return collision_heigth; }	///return: width in maptiles
	float get_bounding_radius();	///return: radius (root square sum of heigth and width) in maptiles
};