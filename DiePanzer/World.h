#pragma once
#include <vector>
#include "Game.h"
#include "GameObject.h"

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
	std::vector<GameObject> objects;

public:
	World();
	~World();
};