include "Tile.h"

using namespace std;

Tile::Tile()
{
	this.z = 0;
}
Tile::Tile(int imgnum, int z)
{
	this.imgnum = imgnum;
	this.z = z;
}