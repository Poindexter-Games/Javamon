#pragma once

#include <cstdint>

class MonsterStats
{
public:
	MonsterStats()
	{
		health = 1;
		speed = 0;
		evasion = 0;
		attack = 0;
		defence = 0;
		stamina = 0;
		magic = 0;
	}
	void setHealth(int health) { MonsterStats::health = health; }
	void setSpeed(int speed) { MonsterStats::speed = speed; }
	void setEvasion(int evasion) { MonsterStats::evasion = evasion; }
	void setAttack(int attack) { MonsterStats::attack = attack; }
	void setDefence(int defence) { MonsterStats::defence = defence; }
	void setStamina(int stamina) { MonsterStats::stamina = stamina; }
	void setMagic(int magic) { MonsterStats::magic = magic; }

	int getHealth() { return health; }
	int getSpeed() { return speed; }
	int getEvasion() { return evasion; }
	int getAttack() { return attack; }
	int getDefence() { return defence; }
	int getStamina() { return stamina; }
	int getMagic() { return magic; }
private:
	int health;
	int speed;
	int evasion;

	int attack;
	int defence;
	int stamina;
	int magic;
};