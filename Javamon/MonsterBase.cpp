#include "MonsterBase.h"

MonsterBase::MonsterBase()
{
	Word w;
	w.langCode = L"code-CODE";
	w.str = L"MONSTER BASE WAS NOT LOADED!\nMONSTER BASE HA LOAD SITTEINAKATTA!!";

	baseStats = MonsterStats();
	incStats = MonsterStats();
}

MonsterBase::MonsterBase(Word w, MonsterStats base, MonsterStats inc)
{
	name = w;
	baseStats = base;
	incStats = inc;
}

void MonsterBase::increaseStats(MonsterStats & stats)
{
	stats.setEvasion(stats.getEvasion() + incStats.getEvasion());

	stats.setHealth(stats.getHealth() + incStats.getHealth());

	stats.setSpeed(stats.getSpeed() + incStats.getSpeed());
}