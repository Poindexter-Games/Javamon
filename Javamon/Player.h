#pragma once
#include <string>
#include <cstdint>

using namespace std;

class Player
{
private:
	bool npc;
	string name;
	int sex; //0 is male, 1 is female

	int x; //block x
	int y; //block y
	int direction;
	float actualX;
	float actualY;
public:
	Player();

	bool isNPC() { return npc; }

	string getName() { return name; }
	bool isMale(){return sex == 0;}
	bool isFemale(){return sex == 1;}
	int getGender() { return sex; };

	void setBlockX(int x) { Player::x = x; }
	void setBlockY(int y) { Player::y = y; }
	void setDirection(int direction) { Player::direction = direction; }
	void setActualX(float actualX) { Player::actualX = actualX; }
	void setActualY(float actualY) { Player::actualY = actualY; }

	void adjustActualX(float adjust) { Player::actualX += adjust; }
	void adjustActualY(float adjust) { Player::actualY += adjust; }


	int getBlockX() { return x; }
	int getBlockY() { return y; }
	int getDirection() { return direction; }
	float getActualX() { return actualX; }
	float getActualY() { return actualY; }
	/*Locked states if the player is seated correctly on the tile*/
	bool lockedX(){return (int)actualX % 64 == 0;}
	bool lockedY(){return (int)actualY % 64 == 0;}
	bool isLocked(){return lockedX() && lockedY();}
};