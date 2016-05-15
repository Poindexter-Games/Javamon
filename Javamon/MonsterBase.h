#pragma once

#include <SFML/System/String.hpp>
#include "MonsterStats.h"
#include "Variables.h"

class MonsterBase
{
public:
	MonsterBase();
	MonsterBase(Word, MonsterStats, MonsterStats);

	void increaseStats(MonsterStats&);
	MonsterStats getBaseStats() { return baseStats; }
	Word getName() { return name; }
private:
	Word name;
	MonsterStats baseStats;
	MonsterStats incStats;
};