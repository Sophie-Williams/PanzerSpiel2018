#include "stdafx.h"
#include "World.h"
#include "GameObject.h"

void World::Apply_moves(uint_fast32_t tick) {
	GameObject* current_object;
	Tank* tank;

	for each (current_object in objects) {
		if (current_object->Get_type() == ClassID::tank_standart) {
			tank = (Tank*)current_object;
			
			Move* current_move = &(tank->Get_move());
			if (current_move->get_tick() == tick) {
				//apply changes

				tank->turret_orientation += current_move->get_turret_rotation();
				tank->chassis_orientation += current_move->get_chassis_rotation();
				tank->speed += current_move->get_acceleration();
			}

			//update position
			

		}
	}
}