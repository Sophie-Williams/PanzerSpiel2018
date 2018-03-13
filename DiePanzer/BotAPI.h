#pragma once
#include <vector>
#include "TankControl.h"
#include <cstdint>

class BotAPI
{
private:
	std::vector<TankControl> mytanks;
	uint32_t tank_amount;
	uint32_t faction;

public:
	void GetEnemyTankInfo(uint32_t tanknr, Tank& tankinfo); 
	uint32_t GetEnemyTankAmount();
};