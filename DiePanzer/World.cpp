#include "stdafx.h"
#include "World.h"
#include "Tank.h"
#include "Game.h"
#include "Eigen/Dense"

using namespace Eigen;

World::World()
{
}

bool World::Initialize()
{
	Graphics* graphics = application->GetGraphicsInterface();
	observer = new GameObserver();

	Vector3f startpos{ 0.0f, 0.0f, -5.0f };
	if (!observer->Initialize(startpos, graphics->GetCamera()))
	{
		return false;
	}

	Tank* tank = new Tank(Vector3f(0.f, 0.f, 0.f));
	tank->Initialize(graphics->GetRenderer()->GetDevice());
	objects.push_back(tank);

	return true;
}

void World::Apply_moves(uint_fast32_t tick) {
	GameObject *object_a, *object_b;
	Tank* tank;
	bool collision = false;

	//update all positions
	for each (object_a in objects) {
		if (object_a->GetIdentity() & ObjectIdentity::Tank) {
			tank = (Tank*)object_a;
			
			Move* current_move = &(tank->Get_move());
			if (current_move->get_tick() == tick) {
				//apply changes

				tank->turret_orientation += current_move->get_turret_rotation();
				tank->chassis_orientation += current_move->get_chassis_rotation();
				tank->speed += current_move->get_acceleration();
			}

			//update position
			tank->coordinates[0] += sin(tank->chassis_orientation)*tank->speed;	//x
			tank->coordinates[1] += cos(tank->chassis_orientation)*tank->speed;	//y
		}
	}

	//check for collisions and resolve them
	do {
		uint_fast32_t i_a, i_b;
		//check each object against every other object
		for (i_a = 0; i_a < objects.size(); i_a++) {
			object_a = objects[i_a];
			for (i_b = i_a + 1; i_b < objects.size(); i_b++) {
				object_b = objects[i_b];

				
			}
		}
			
	} while (collision);
}