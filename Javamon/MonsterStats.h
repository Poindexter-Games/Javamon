#pragma once

#include <cstdint>

class MonsterStats
{
public:
	MonsterStats()
	{
		health = 1;
	}
	void setHealth(int health) { MonsterStats::health = health; }
	void setSpeed(int speed) { MonsterStats::speed = speed; }
	/*
	Evasion is an int from 0 to 100 (both values inclusive),
	determines monster's success chance at dodging an attack.
	*/
	void setEvasion(int evasion) { MonsterStats::evasion = evasion; }

	int getHealth() { return health; }
	int getSpeed() { return speed; }
	/*
	Evasion is an int from 0 to 100 (both values inclusive),
	determines monster's success chance at dodging an attack.
	*/
	int getEvasion() { return evasion; }
private:
	int health;
	int speed;
	int evasion;
};