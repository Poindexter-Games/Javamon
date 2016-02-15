#pragma once

#include <cstdint>
#include <SFML/System/String.hpp>

#include "Entity.h"

#include "StringEditor.h"
#include "Variables.h"

using namespace std;

//THIS CLASS NEEDS TO BE BROKEN INTO A .CPP FILE
//KARL PIEPHO

class Teleport: public Entity
{
public:
	/*Default Constructor, creates an inreachable teleport*/
	Teleport(): Entity(-2, -2)
	{
		toAnotherLevel = false;
		toX = -2;
		toY = -2;
		zdirection = 0;
		direction = Direction::UP;
		steepness = 0;
		rug = false;
	}
	/*
	Intra-level teleport
	Author: Karl Piepho
	Date Created: 1/16/2016
	Date Revised: 2/15/2016
	Params:
	Type: 0 if standard teleport, 1 if going upstairs, -1 if going downstairs
	*/
	Teleport(int x, int y, int toX, int toY, Direction direction, int zdirection, float steepness): Entity(x, y)
	{
		toAnotherLevel = false;
		Teleport::toX = toX;
		Teleport::toY = toY;
		Teleport::zdirection = zdirection;
		Teleport::direction = direction;
		Teleport::steepness = steepness;
		StringEditor::echo(Teleport::steepness);
		rug = false;

		StringEditor::echo(L"Local Teleport Constructed, Steepness:");
		StringEditor::echo(Teleport::steepness);
	}
	/*
	Inter-level teleport
	Author: Karl Piepho
	Date Created: 1/16/2016
	Params:
	Type: 0 if standard teleport, 1 if going upstairs, -1 if going downstairs
	*/
	Teleport(int x, int y, sf::String name, int toX, int toY, Direction direction, int zdirection, float steepness) : Entity(x, y)
	{
		toAnotherLevel = true;
		Teleport::name = name;
		Teleport::toX = toX;
		Teleport::toY = toY;
		Teleport::zdirection = zdirection;
		Teleport::direction = direction;
		Teleport::steepness = steepness;
		rug = false;
	}

	int getX() { return x; }
	int getY() { return y; }
	int getToX() { return toX; }
	int getToY() { return toY; }
	Direction getDirection(){return direction;}
	int getZDirection() { return zdirection; }
	float getSteepness() { return steepness; }
	bool interLevel() { return toAnotherLevel; }
	bool intraLevel() { return !toAnotherLevel; }
	sf::String getName() { return name; }
	bool drawRug() { return rug; }
	int rugNum() { return texture; }

	float switchSteepness()
	{
		if (steepness == .25f)
			return .5f;
		return .25f;
	}
private:
	int toX;
	int toY;
	Direction direction; //0 up, 1 left, 2 down, 3 right
	bool toAnotherLevel;
	sf::String name;
	int zdirection; //0 if standard teleport, 1 if up stairs, -1 if down stairs
	float steepness; //.25f for upper floors (SHALLOW), .5f for lower floors (STEEP)
	bool rug; //if true, level will draw a rug at teleport's location TODO
	int texture; //texture number for teleport rug TODO
};