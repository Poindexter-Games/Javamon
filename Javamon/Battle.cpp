#include "Battle.h"

Battle::Battle()
{
	bg = sf::RectangleShape();
	bg.setSize(sf::Vector2f((float)INT_MAX, (float)INT_MAX));
	bg.setFillColor(sf::Color::White);
	bg.setPosition(sf::Vector2f(INT_MIN / 2, INT_MIN / 2));
}

void Battle::update(bool* digitalControls)
{

}

void Battle::render(sf::RenderWindow & window)
{
	window.draw(bg);
}
