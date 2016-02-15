#include "MovableEntity.h"

MovableEntity::MovableEntity(int x, int y) :Entity(x, y)
{
	actualX = (float)(x * BLOCK_SIZE);
	actualY = (float)(y * BLOCK_SIZE);
}

void MovableEntity::render(sf::RenderWindow & w)
{
	sf::RectangleShape a;
	a.setFillColor(sf::Color::Cyan);
	a.setPosition(sf::Vector2f(actualX, actualY));
	a.setSize(sf::Vector2f((float)BLOCK_SIZE, (float)BLOCK_SIZE));
	w.draw(a);
}
