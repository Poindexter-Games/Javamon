#pragma once

#include <SFML/System/String.hpp>

#include "StringEditor.h"

#include "Variables.h"
#include "MonsterBase.h"
#include "MonsterStats.h"

using namespace std;

class Monster
{
public:
	Monster();
	Monster(sf::String, Sex); //monsters for debug

	void restore() { health = stats.getHealth(); }

	sf::String getName() { return name; }
	Sex getSex() { return sex; }
	int getHealth() { return health; }
	MonsterStats getStats() { return stats; }
private:
	MonsterBase base;
	sf::String name;
	Sex sex;
	MonsterStats stats;
	int health;
};