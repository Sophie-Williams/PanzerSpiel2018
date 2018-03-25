#pragma once
#include "Vector.h"
#include <vector>
#include<cstdint>
#include "GameObject.h"

//forward declarations
class World;

/**
 * 
 *
**/
class ICollidable: public GameObject {
protected:
	Vector2* vertices;
	uint_fast32_t vertices_amount;
	Vector2 bounding_circle_offset;
	float bounding_circle_radius;

	ICollidable(float heigth, float width);
	~ICollidable();

public:
	const Vector2* get_vertices() { return vertices; }	///return: array of Vector2. The edges of the ICollidable are spanned from one vertex to the next in this array and from the last to the first.
	uint_fast32_t get_vertices_amount() { return vertices_amount; } ///return: number of vertices in get_vertices(). maximum index is one less.
	float get_bounding_radius() {return bounding_circle_radius;}	///return:  in maptiles

	bool check_for_collision(ICollidable* obj1, ICollidable* obj2);	/// return: true if objects collide
	bool check_for_collision(ICollidable* obj, World* map);	///return: true if object collides with the map

};

