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
	string pack;
	string name;
public:
	/*
	Intra-level teleport
	Author: Karl Piepho
	Date Created: 1/16/2016
	*/
	Teleport(int x, int y, int toX, int toY, int direction)
	{
		toAnotherLevel = false;
		Teleport::x = x;
		Teleport::y = y;
		Teleport::toX = toX;
		Teleport::toY = toY;
		Teleport::direction = direction;
	}
	/*
	Inter-level teleport
	Author: Karl Piepho
	Date Created: 1/16/2016
	*/
	Teleport(int x, int y, string pack, string name, int toX, int toY, int direction)
	{
		toAnotherLevel = true;
		Teleport::x = x;
		Teleport::y = y;
		Teleport::pack = pack;
		Teleport::name = name;
		Teleport::toX = toX;
		Teleport::toY = toY;
		Teleport::direction = direction;
	}

	int getX() { return x; }
	int getY() { return y; }
	int getToX() { return toX; }
	int getToY() { return toY; }
	bool interLevel() { return toAnotherLevel; }
	bool intraLevel() { return !toAnotherLevel; }
	string getPack() { return pack; }
	string getName() { return name; }
};