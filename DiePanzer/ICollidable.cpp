#include "stdafx.h"
#include "ICollidable.h"
#include <cmath>

ICollidable::ICollidable(float heigth, float width) {
	
	bounding_circle_offset = Vector2(0, 0);
	bounding_circle_radius = hypot(heigth, width);

	vertices = new Vector2[4];
	vertices_amount = 4;
	
	//Order is important! The order defines the edges of the object: vertices[n] -> vertices[(n+1)%vertices_amount] 
	vertices[0].Init(heigth, width);
	vertices[1].Init(-heigth, width);
	vertices[2].Init(-heigth, -width);
	vertices[3].Init(heigth, -width);
}

ICollidable::~ICollidable() {
	delete vertices;
}

bool ICollidable::check_for_collision(ICollidable* obj1, ICollidable* obj2) {
	
	//check bounding circles:
	//TODO: implement rotations for GameObjects and rotate the bounding_circle_offset vectors
	if (((obj1->coordinates + obj1->bounding_circle_offset) - (obj2->coordinates + obj2->bounding_circle_offset)).Length() > (obj1->bounding_circle_radius + obj2->bounding_circle_radius)) {
		//bounding_circles don't intersect -> no collision
		return false;
	}

	//TODO: quick check by rotating to each reference system and check for vertices inside other object? should catch many cases and be faster than checking each edge
	//if () { //obj1 in obj2
	//	return true;
	//}
	//if () {	//obj2 in obj1
	//	return true;
	//}


	//check edges
	for (uint_fast32_t index1 = 0; index1 < obj1->vertices_amount; index1++) {
		for (uint_fast32_t index2 = 0; index2 < obj2->vertices_amount; index2++) {
			//check for 
		}
	}


	
	return false;
}

bool ICollidable::check_for_collision(ICollidable* obj, World* map) {
	return false;
}