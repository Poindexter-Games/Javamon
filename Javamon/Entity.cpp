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