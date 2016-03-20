#include "Player.h"
Player::Player(): MovableEntity(0, 0)
{
	//common stuff
	name = L"Gei Hakkâ";
	sex = Sex::FEMALE;
	x = 0;
	y = 0;
	direction = Direction::DOWN;
	zdirection = 0;
	actualX = 0;
	actualY = 0;
	movementAllowed = true;
	mode = Mode::NORMAL;

	menu = InGameMenu();

	dialog = L"THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG.";
	anteBattleQuote = L"BATTLE QUOTE NOT LOADED.";
	postBattleQuote = L"BATTLE QUOTE NOT LOADED.";
	npcDialogNumber = -1;

	//npc related stuff
	visible = true;
	animationFrame = 0;
	wantsToBattle = false;

	sf::Image textureSheet;
	textureSheet.loadFromFile(VIDEO + L"Player.png");


	textures.resize(16);
	for (int i = 0; i < 16; i++)
	{
		textures[i].loadFromImage(textureSheet, sf::IntRect((i % 16) * BLOCK_SIZE, (int)((i - (i % 16)) / 16) + (PLAYER_HEIGHT * sex), BLOCK_SIZE, PLAYER_HEIGHT));
	}
}

void Player::render(sf::RenderWindow & w)
{
	sf::Sprite s(textures[(direction * 4) + animationFrame]);
	if (zdirection == 0)
	{
		s.setPosition(sf::Vector2f(actualX, actualY - (PLAYER_HEIGHT - BLOCK_SIZE)));
	}
	else if (direction == Direction::LEFT)
	{
		s.setPosition(sf::Vector2f(actualX, actualY - (PLAYER_HEIGHT - BLOCK_SIZE) - (zdirection * steepness * (BLOCK_SIZE - (actualX - (x * 64))))));
	}
	else if (direction == Direction::RIGHT)
	{
		s.setPosition(sf::Vector2f(actualX, actualY - (PLAYER_HEIGHT - BLOCK_SIZE) - (zdirection * steepness * (BLOCK_SIZE - ((x * 64) - actualX)))));
	}
	
	w.draw(s);
}

void Player::renderMenu(sf::RenderWindow & w)
{
	sf::View view;
	view.setCenter(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	view.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	w.setView(view);
	menu.render(w);
}

void Player::place(int x, int y, Direction d)
{
	Player::x = x;
	Player::y = y;
	actualX = (float)(x * BLOCK_SIZE);
	actualY = (float)(y * BLOCK_SIZE);
	direction = d;
	zdirection = 0;
	steepness = 0;

	animationFrame = 0;
}

void Player::place(int x, int y, Direction d, int zdir, float s)
{
	/*
	TODO
	THIS METHOD IS AWFUL, THIS NEEDS TO BE CHANGED.
	*/

	Player::x = x;
	Player::y = y;
	actualX = (float)(x * BLOCK_SIZE);
	actualY = (float)(y * BLOCK_SIZE);
	if (d == Direction::LEFT)
	{
		if (zdir != 0)
		{
			actualX = (float)((x * BLOCK_SIZE) + (.75f * BLOCK_SIZE));
		}
	}
	else if (d == Direction::RIGHT)
	{
		if (zdir != 0)
		{
			actualX = (float)((x * BLOCK_SIZE) - (.75f * BLOCK_SIZE));
		}
	}
		
	direction = d;
	zdirection = zdir;
	steepness = s;

	animationFrame = 0;
}