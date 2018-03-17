#pragma once
#include <vector>
#include "Game.h"
#include "GameObject.h"
#include "Tank.h"
#include <cstdint>
#include <cmath>

#define WORLD_DEFAULT_WIDTH 800
#define WORLD_DEFAULT_HEIGHT 600

class MapTile
{
	uint8_t properties;
};

class World
{
private:
	MapTile map[WORLD_DEFAULT_WIDTH][WORLD_DEFAULT_HEIGHT];
	std::vector<GameObject*> objects;

public:
	World();
	~World();

	void Apply_moves(uint_fast32_t tick);
};