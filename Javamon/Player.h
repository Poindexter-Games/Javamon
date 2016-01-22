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
	int zdirection; //this is for the going up stairs or down stairs animation, 1 is up, -1 is down
	float actualX;
	float actualY;
	bool movementAllowed;

	string anteBattleQuote; //Quote before the battle
	string postBattleQuote; //Quote after the battle
public:
	Player();

	bool isNPC() { return npc; }

	string getName() { return name; }
	bool isMale(){return sex == 0;}
	bool isFemale(){return sex == 1;}
	int getGender() { return sex; };

	void setBlockX(int x) { Player::x = x;}
	void setBlockY(int y) { Player::y = y;}
	void setDirection(int direction) { Player::direction = direction; }
	void setZDirection(int zd) { zdirection = zd; }
	void setActualX(float actualX) { Player::actualX = actualX; }
	void setActualY(float actualY) { Player::actualY = actualY; }

	void adjustActualX(float adjust) { Player::actualX += adjust; }
	void adjustActualY(float adjust) { Player::actualY += adjust; }

	void allowMovement() { movementAllowed = true; }
	void inhibitMovement() { movementAllowed = false; }
	bool isAllowedToMove() { return movementAllowed; }

	int getBlockX() { return x; }
	int getBlockY() { return y; }
	int getDirection() { return direction; }
	int getZDirection() { return zdirection; }
	float getActualX() { return actualX; }
	float getActualY() { return actualY; }
	bool lockedX(){return (int)actualX % 64 == 0;}
	bool lockedY(){return (int)actualY % 64 == 0;}
	/*Locked states if the player is seated correctly on the tile*/
	bool isLocked(){return lockedX() && lockedY();}
};