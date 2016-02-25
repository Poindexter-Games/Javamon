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
	Monster(sf::String); //monsters for debug

	void restore() { health = stats.getHealth(); }

	int getHealth() { return health; }
private:
	MonsterBase base;
	sf::String name;
	Gender sex;
	MonsterStats stats;
	int health;
};