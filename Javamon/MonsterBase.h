#pragma once

#include "MonsterStats.h"

class MonsterBase
{
public:
	MonsterBase();

	void increaseStats(MonsterStats&);
	MonsterStats getBaseStats() { return baseStats; }
private:
	MonsterStats baseStats;
	MonsterStats incStats;
};