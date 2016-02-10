#pragma once

/*
Defines a class for displaying special tiles and or people in the Level

Author: Karl Piepho
Date Created: Feb 4, 2016
Date Revised: Feb 4, 2016
*/
class Entity
{
public:
	/*
	Creates an entity that holds what block it is on
	*/
	Entity(int, int);
	virtual ~Entity();
	int getX();
	int getY();
protected:
private:
	int x;
	int y;
};