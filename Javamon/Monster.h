#pragma once

#include <string>
#include <cstdint>

#include "Variables.h"
#include "MonsterBase.h"
#include "MonsterStats.h"

using namespace std;

class Monster
{
public:
	Monster();

	void restore() { health = stats.getHealth(); }

	int getHealth() { return health; }
private:
	MonsterBase base;
	string name;
	Gender sex;
	MonsterStats stats;
	int health;
};