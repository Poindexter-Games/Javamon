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
	actualX = 0;
	actualY = 0;

	anteBattleQuote = "...";
	postBattleQuote = "Hah!";

	//npc related stuff
}