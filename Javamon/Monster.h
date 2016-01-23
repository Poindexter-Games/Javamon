#pragma once

#include <string>
#include <cstdint>

#include "Variables.h"
#include "MonsterBase.h"
#include "MonsterStats.h"

using namespace std;

class Monster
{
private:
	MonsterBase base;
	string name;
	Gender sex;
	MonsterStats stats;
	int currentHealth;
public:
	Monster();

	void restore() { currentHealth = stats.getHealth(); }

	int getCurrentHealth() { return currentHealth; }
};