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

	dialog = "DIALOG NOT LOADED.";
	anteBattleQuote = "BATTLE QUOTE NOT LOADED.";
	postBattleQuote = "BATTLE QUOTE NOT LOADED.";

	numMonsters = 0;

	//npc related stuff
	visible = true;
	wantsToBattle = false;
}
Player::Player(string quote)
{
	Player::dialog = quote;

	npc = true;

	//common stuff
	name = "Pedestrian";
	sex = Gender::MALE;
	x = 0;
	y = 0;
	direction = Direction::DOWN;
	zdirection = 0;
	actualX = 0;
	actualY = 0;
	movementAllowed = false;

	anteBattleQuote = "HOW DID YOU START A BATTLE WITH ME?";
	postBattleQuote = "HOW DID YOU DEFEAT ME?";

	numMonsters = 0;

	//npc related stuff
	visible = true;
	wantsToBattle = false;
}
Player::Player(string quote, Monster* party, int partySize)
{
	Player::dialog = quote;

	npc = true;

	//common stuff
	name = "Trainer";
	sex = Gender::MALE;
	x = 0;
	y = 0;
	direction = Direction::DOWN;
	zdirection = 0;
	actualX = 0;
	actualY = 0;
	movementAllowed = false;

	anteBattleQuote = "You'll never beat me!";
	postBattleQuote = "You're too good!";

	monsters = party;
	numMonsters = partySize;

	//npc related stuff
	visible = true;
	wantsToBattle = true;
}