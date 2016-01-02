#pragma once
#include <cstdint>

using namespace std;

class Tile
{
private:
	int imgnum;
	int z;
public:
	Tile();
	Tile(int, int);

	void setImgNum() {Tile::imgnum = imgnum;}
	int getImgNum(){return imgnum;}

	void setZ(int z){Tile::z = z;} //Does this really work?
	int getZ(){return z;}
};