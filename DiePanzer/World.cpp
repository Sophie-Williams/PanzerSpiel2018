#include "stdafx.h"
#include "World.h"
#include "GameObject.h"

void World::Apply_moves(uint_fast32_t tick) {
	for each (GameObject* currentObject in objects) {
		if (currentObject->Get_type() == ClassID::tank_standart) {
			Tank* tank = (Tank*)currentObject;			
		}
	}
}