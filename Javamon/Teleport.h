#pragma once
#include <cstdint>
#include <string>

using namespace std;

class Teleport
{
private:
	int x;
	int y;
	int toX;
	int toY;
	int direction; //0 up, 1 left, 2 down, 3 right
	bool toAnotherLevel;
	string name;
	int zdirection; //0 if standard teleport, 1 if up stairs, -1 if down stairs
	bool rug; //if true, level will draw a rug at teleport's location TODO
	int texture; //texture number for teleport rug TODO
public:
	/*Default Constructor, creates an inreachable teleport*/
	Teleport()
	{
		toAnotherLevel = false;
		x = -2;
		y = -2;
		toX = -2;
		toY = -2;
		zdirection = 0;
		direction = 0;
		rug = false;
	}
	/*
	Intra-level teleport
	Author: Karl Piepho
	Date Created: 1/16/2016
	Params:
	Type: 0 if standard teleport, 1 if going upstairs, -1 if going downstairs
	*/
	Teleport(int x, int y, int toX, int toY, int direction, int zdirection)
	{
		toAnotherLevel = false;
		Teleport::x = x;
		Teleport::y = y;
		Teleport::toX = toX;
		Teleport::toY = toY;
		Teleport::zdirection = zdirection;
		Teleport::direction = direction;
		rug = false;
	}
	/*
	Inter-level teleport
	Author: Karl Piepho
	Date Created: 1/16/2016
	Params:
	Type: 0 if standard teleport, 1 if going upstairs, -1 if going downstairs
	*/
	Teleport(int x, int y, string name, int toX, int toY, int direction, int zdirection)
	{
		toAnotherLevel = true;
		Teleport::x = x;
		Teleport::y = y;
		Teleport::name = name;
		Teleport::toX = toX;
		Teleport::toY = toY;
		Teleport::zdirection = zdirection;
		Teleport::direction = direction;
		rug = false;
	}

	int getX() { return x; }
	int getY() { return y; }
	int getToX() { return toX; }
	int getToY() { return toY; }
	int getDirection(){return direction;}
	int getZDirection() { return zdirection; }
	bool interLevel() { return toAnotherLevel; }
	bool intraLevel() { return !toAnotherLevel; }
	string getName() { return name; }
	bool drawRug() { return rug; }
	int rugNum() { return texture; }
};