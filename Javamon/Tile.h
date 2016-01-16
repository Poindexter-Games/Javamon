#pragma once
#include <cstdint>

using namespace std;

class Tile
{
private:
	int imgnum;
	int z;
	int type; //0 for ground, 1 for water, 2 for filler
public:
	Tile();
	/*
	Params:
	imgnum - int
	z      - int
	type   - int
	*/
	Tile(int, int, int);

	void setImgNum() {Tile::imgnum = imgnum;}
	int getImgNum(){return imgnum;}

	void setZ(int z){Tile::z = z;}
	int getZ(){return z;}

	void setType(int z){Tile::type = type;}
	int getType(){return type;}

	static bool movementValid(Tile a, Tile b)
	{
		return (a.type == b.type) && (a.z +	1 >= b.z);
	}
};