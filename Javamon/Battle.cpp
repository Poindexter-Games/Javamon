#include "Battle.h"

Battle::Battle()
{
	running = true;
	numFrames = 0;

	bg = sf::RectangleShape();
	bg.setSize(sf::Vector2f((float)INT_MAX, (float)INT_MAX));
	bg.setFillColor(sf::Color::White);
	bg.setPosition(sf::Vector2f(INT_MIN / 2, INT_MIN / 2));
}

void Battle::render(sf::RenderWindow & window, int playerNumber)
{
	//
}

void Battle::update(Controls& c, int playerNumber)
{
	//
}
