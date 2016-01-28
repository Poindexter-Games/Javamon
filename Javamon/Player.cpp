#include "Player.h"
Player::Player()
{
	npc = false;

	//common stuff
	name = L"Gei Hakkâ";
	sex = Gender::MALE;
	x = 0;
	y = 0;
	direction = Direction::DOWN;
	zdirection = 0;
	actualX = 0;
	actualY = 0;
	movementAllowed = true;

	dialog = L"THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG.";
	anteBattleQuote = L"BATTLE QUOTE NOT LOADED.";
	postBattleQuote = L"BATTLE QUOTE NOT LOADED.";

	numMonsters = 0;

	//npc related stuff
	visible = true;
	wantsToBattle = false;
}
Player::Player(wstring quote)
{
	Player::dialog = quote;

	npc = true;

	//common stuff
	name = L"Pedestrian";
	sex = Gender::MALE;
	x = 0;
	y = 0;
	direction = Direction::DOWN;
	zdirection = 0;
	actualX = 0;
	actualY = 0;
	movementAllowed = false;

	dialog = L"It is nice and sunny out today.";
	anteBattleQuote = L"HOW DID YOU START A BATTLE WITH ME?";
	postBattleQuote = L"HOW DID YOU DEFEAT ME?";

	numMonsters = 0;

	//npc related stuff
	visible = true;
	wantsToBattle = false;
}
Player::Player(wstring quote, Monster* party, int partySize)
{
	Player::dialog = quote;

	npc = true;

	//common stuff
	name = L"Trainer";
	sex = Gender::MALE;
	x = 0;
	y = 0;
	direction = Direction::DOWN;
	zdirection = 0;
	actualX = 0;
	actualY = 0;
	movementAllowed = false;

	quote = L"Fix this quote later?";
	anteBattleQuote = L"You'll never beat me!";
	postBattleQuote = L"You're too good!";

	monsters = party;
	numMonsters = partySize;

	//npc related stuff
	visible = true;
	wantsToBattle = true;
}