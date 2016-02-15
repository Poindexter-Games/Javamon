#include "Entity.h"

Entity::Entity(int x, int y)
{
	Entity::x = x;
	Entity::y = y;
}

Entity::~Entity()
{
}

int Entity::getX()
{
	return x;
}

int Entity::getY()
{
	return y;
}

void Entity::setX(int x)
{
	Entity::x = x;
}

void Entity::setY(int y)
{
	Entity::y = y;
}

void Entity::render(sf::RenderWindow & w)
{
	sf::RectangleShape square;
	square.setPosition(sf::Vector2f(x * BLOCK_SIZE, y * BLOCK_SIZE));
	square.setSize(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
	square.setFillColor(sf::Color::White);
	w.draw(square);
	
}
