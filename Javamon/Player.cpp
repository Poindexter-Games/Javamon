#include "Player.h"
Player::Player()
{
	npc = false;

	//common stuff
	name = "Gei Hakka";
	sex = 0;
	x = 0;
	y = 0;
	direction = 2;
	zdirection = 0;
	actualX = 0;
	actualY = 0;
	movementAllowed = true;

	anteBattleQuote = "Oré wha o'chinchin ga daiski nanda yo!";
	postBattleQuote = "Oré wha o'chinchin ga daiski nanda yo!";

	//npc related stuff
}