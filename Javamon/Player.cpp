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

	anteBattleQuote = "Or� wha o'chinchin ga daiski nanda yo!";
	postBattleQuote = "Or� wha o'chinchin ga daiski nanda yo!";

	//npc related stuff
}