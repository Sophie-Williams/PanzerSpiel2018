#pragma once
#include <vector>
#include "Game.h"
#include "GameObject.h"

class MapTile
{
	uint8_t properties;
};

class World
{
private:
	MapTile map[Game::mapsize_x][Game::mapsize_y];
	std::vector<GameObject> objects;

public:
	World();
	~World();
};