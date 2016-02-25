#include "MonsterBase.h"

MonsterBase::MonsterBase()
{
	baseStats = MonsterStats();
	incStats = MonsterStats();
}

void MonsterBase::increaseStats(MonsterStats & stats)
{
	stats.setEvasion(stats.getEvasion() + incStats.getEvasion());

	stats.setHealth(stats.getHealth() + incStats.getHealth());

	stats.setSpeed(stats.getSpeed() + incStats.getSpeed());
}
