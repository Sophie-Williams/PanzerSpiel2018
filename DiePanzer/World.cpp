#include "stdafx.h"
#include "World.h"
#include "GameObject.h"

void World::Apply_moves(uint_fast32_t tick) {
	GameObject* current_object;
	Tank* tank;

	for each (urrentObject in objects) {
		if (current_object->Get_type() == ClassID::tank_standart) {
			tank = (Tank*)current_object;
			
			Move current_move* = tank->Get_move();
			if (current_move->tick == tick) {
				//apply changes

				tank->turret_orientation += current_move->cannon_rotation;
				tank->chassis_orientation += current_move->chassis_rotation;
				tank->speed += current_move->acceleration;
			}



		}
	}
}