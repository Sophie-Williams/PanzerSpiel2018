#pragma once
#include <Windows.h>
#include <cstdint>
#include "Callback.h"
#include "Singleton.h"

//forward declarations
class World;


class Game : public Singleton<Game>
{	
private:
	uint32_t tick;	
	World* world;

public:
	Callback<uint32_t> CreateMove;	
	void Setup();
	void MainLoop();
};
