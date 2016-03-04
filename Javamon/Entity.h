#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Variables.h"

/*
Defines a class for displaying special tiles and or people in the Level

Author: Karl Piepho
Date Created: Feb 4, 2016
Date Revised: March 3, 2016
*/
class Entity
{
public:
	/*
	Creates an entity that holds what block it is on
	*/
	Entity(int, int);
	virtual ~Entity();
	/*
	Block X
	*/
	int getX();
	/*
	Block Y
	*/
	int getY();
	/*
	Block X
	*/
	void setX(int);
	/*
	Block Y
	*/
	void setY(int);
	/*
	Render an entity. This method needs to be overriden.
	*/
	void render(sf::RenderWindow&);
protected:
	/*
	Block X
	*/
	int x;
	/*
	Block Y
	*/
	int y;
private:
};