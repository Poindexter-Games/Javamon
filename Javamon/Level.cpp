#include "Level.h"

using namespace std;

Level::Level()
{
	this.pack = "Karl"; //I don't want to bother with spelling poindexter
	this.name = "Test";
	int width = 8;
	int height = 8;
	map = Tile[width][height];
	for(int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			map[i][j] = Tile(0, 0);
		}
	}
	textureMap = sf::Texture();
}

Level::Level(string name)
{
	this.name = name;
}

Level::Level(string pack, string level)
{
	/*We and mod developers all have seperate packs so that level name conflicts don't occur.
	Therefore, our pack is designated as: Default*/

	//TODO Implement loading from resource/pack/level.txt
	name = level;
}

void Level::render(sf::RenderWindow window&)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			Texture t();
			
		}
	}
}

void Level::setName(string name)
{
	this.name = name;
}