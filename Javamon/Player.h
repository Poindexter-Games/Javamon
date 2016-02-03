#pragma once
#include <string>
#include <cstdint>

#include "Variables.h"
#include "Monster.h"

using namespace std;

class Player
{
private:
	bool npc;
	wstring name;
	Gender sex;

	int x; //block x
	int y; //block y
	Direction direction;
	int zdirection; //this is for the going up stairs or down stairs animation, 1 is up, -1 is down
	float actualX;
	float actualY;
	bool movementAllowed;

	wstring dialog; //Dialogue
	wstring anteBattleQuote; //Quote before the battle
	wstring postBattleQuote; //Quote after the battle

	bool wantsToBattle;
	Monster* monsters; //Inventory of monsters
	int numMonsters; //Number of monsters in inventory. This must be between 0 and 6 (inclusive).

	bool visible; //If true, shows NPC and gives them a hitbox
public:
	Player(); //
	Player(wstring); //Talking NPC
	Player(wstring, Monster* party, int partySize); //Battling NPC

	bool isNPC() { return npc; }

	wstring getName() { return name; }
	bool isMale(){return sex == 0;}
	bool isFemale(){return sex == 1;}
	void setGender(Gender sex) { Player::sex = sex; }
	Gender getGender() { return sex; };

	void setBlockX(int x) { Player::x = x;}
	void setBlockY(int y) { Player::y = y;}
	void setDirection(Direction direction) { Player::direction = direction; }
	void setZDirection(int zd) { zdirection = zd; }
	void setActualX(float actualX) { Player::actualX = actualX; }
	void setActualY(float actualY) { Player::actualY = actualY; }
	void place(int, int, Direction);

	void adjustActualX(float adjust) { Player::actualX += adjust; }
	void adjustActualY(float adjust) { Player::actualY += adjust; }

	void allowMovement() { movementAllowed = true; }
	void inhibitMovement() { movementAllowed = false; }
	bool isAllowedToMove() { return movementAllowed; }

	int getBlockX() { return x; }
	int getBlockY() { return y; }
	Direction getDirection() { return direction; }
	int getZDirection() { return zdirection; }
	float getActualX() { return actualX; }
	float getActualY() { return actualY; }
	bool lockedX(){return (int)actualX % 64 == 0;}
	bool lockedY(){return (int)actualY % 64 == 0;}
	/*Locked states if the player is seated correctly on the tile*/
	bool isLocked(){return lockedX() && lockedY();}

	wstring getDialog() { return dialog; }
	wstring getPostBattleQuote() { return postBattleQuote; }
	wstring getAnteBattleQuote() { return anteBattleQuote; }

	void setDialog(wstring dialog) { Player::dialog = dialog; }

	bool isVisible(){return visible;}
	void setVisible() { visible = true; }
	void setInvisible() { visible = false; }

	bool getWantsToBattle() { return wantsToBattle; }
	void setWantsToBattle(bool b) { wantsToBattle = b; }
};