#include "Tile.h"

using namespace std;

Tile::Tile() :Entity(0, 0)
{
	Tile::imgnum = 0;
	Tile::z = 0;
	Tile::type = 0;
}
Tile::Tile(int imgnum, int z, int type): Entity(0, 0)
{
	Tile::imgnum = imgnum;
	Tile::z = z;
	Tile::type = type;
}