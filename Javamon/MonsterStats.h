#pragma once

#include <cstdint>

class MonsterStats
{
private:
	int health;
public:
	MonsterStats()
	{
		health = 1;
	}

	void setHealth(int health) { MonsterStats::health = health; }

	int getHealth() { return health; }
};