#include "Monster.h"

Monster::Monster()
{
	name = L"Gei Hakkâ's Monster";
	base = MonsterBase();
	stats = base.getBaseStats();	//get the stats from the base
	sex = Gender::MALE;
	health = stats.getHealth();
}

Monster::Monster(sf::String name)
{
	Monster::name = name;
	//monster base
	stats = MonsterStats();	//get the stats from the base

	if (StringEditor::equals(name, L"tanaco"))
	{
		sex = Gender::FEMALE;
	}
	if (StringEditor::equals(name, L"migaca"))
	{
		sex = Gender::FEMALE;
	}
	if (StringEditor::equals(name, L"sacatu"))
	{
		sex = Gender::FEMALE;
	}
	if (StringEditor::equals(name, L"kiyumi"))
	{
		sex = Gender::FEMALE;
	}
	else
	{
		sex = Gender::MALE;
	}
	health = stats.getHealth();
}