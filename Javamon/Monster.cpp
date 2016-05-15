#include "Monster.h"

Monster::Monster()
{
	name = L"Name Undefined";
	base = MonsterBase();
	stats = base.getBaseStats();	//get the stats from the base
	sex = Sex::MALE;
	health = stats.getHealth();
}

Monster::Monster(wstring name, Sex sex)
{
	Monster::name = name;
	Monster::sex = sex;
	//monster base
	stats = MonsterStats();	//get the stats from the base

	health = stats.getHealth();
}