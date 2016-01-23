#include "Player.h"
Player::Player()
{
	npc = false;

	//common stuff
	name = "Gei Hakkâ";
	sex = Gender::MALE;
	x = 0;
	y = 0;
	direction = Direction::DOWN;
	zdirection = 0;
	actualX = 0;
	actualY = 0;
	movementAllowed = true;

	anteBattleQuote = "Oré wha o'chinchin ga daiski nanda yo!";
	postBattleQuote = "Oré wha o'chinchin ga daiski nanda yo!";

	numMonsters = 0;

	//npc related stuff
	visible = true;
}