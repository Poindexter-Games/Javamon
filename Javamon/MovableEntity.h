#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "Entity.h"

#include "Variables.h"

class MovableEntity :public Entity
{
public:
	MovableEntity(int, int);
	void render(sf::RenderWindow&);

	void setActualX(float x) { actualX = x; }
	void setActualY(float y) { actualY = y; }

	void adjustActualX(float adjust) { actualX += adjust; }
	void adjustActualY(float adjust) { actualY += adjust; }

	float getActualX() { return actualX; }
	float getActualY() { return actualY; }
	bool isLocked() { return lockedX() && lockedY(); }
protected:
	float actualX;
	float actualY;
private:
	bool lockedX() { return (int)actualX % BLOCK_SIZE == 0; }
	bool lockedY() { return (int)actualY % BLOCK_SIZE == 0; }
};