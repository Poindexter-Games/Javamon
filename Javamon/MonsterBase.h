#pragma once

#include <SFML/System/String.hpp>
#include "MonsterStats.h"

class MonsterBase
{
public:
	MonsterBase();

	void increaseStats(MonsterStats&);
	MonsterStats getBaseStats() { return baseStats; }
	sf::String getName() { return name; }
private:
	sf::String name;
	MonsterStats baseStats;
	MonsterStats incStats;
};