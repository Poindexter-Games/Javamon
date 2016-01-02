#include "Level.h"

using namespace std;

Level::Level()
{
	Level::pack = "Karl"; //I don't want to bother with spelling poindexter
	Level::name = "Test";
	width = 8;
	height = 8;

	map = new Tile*[width];
	for(int i = 0; i < width; i++)
	{
		map[i] = new Tile[height];
	}
	for(int i = 0; i < width; i++)
	{
		for(int j = 0; j < height; j++)
		{
			map[i][j] = Tile(0, 0);
		}
	}
	map[1][1] = Tile(1, 0);

	textureMap = sf::Image();
	textureMap.loadFromFile("C:/Users/Karl/Source/Repos/Javamon/Javamon/Resources/Levels/" + pack + "/" + name + "/Spritesheet.png");

	/*
	//Listening to Leeroy jenkins remix 10 hours
	//Time straight = 54:07 (54 minutes 07 seconds) I couldn't make it to an hour...
	
	for(int i = 0; i < blocks.size(); i++)
	{	
		g.drawImage(images.get(blocks.get(i).imageId()), ((i%width)*60)+xOffset, (Math.roundDown(i/width)*60)+yOffset, null);
	}
	*/

	textures = new sf::Texture[256];
	for(int i = 0; i < 256; i++) //Creates a list of textures from the spritesheet
	{
		textures[i] = sf::Texture();
		textures[i].loadFromImage(textureMap, sf::IntRect((i % width)*64, (int)(i / width) * 64, 64, 64));
	}
}

Level::Level(string name)
{
	Level::name = name;
}

Level::Level(string pack, string level)
{
	/*We and mod developers all have seperate packs so that level name conflicts don't occur.
	Therefore, our pack is designated as: Default*/

	//TODO Implement loading from resource/pack/level.txt
	name = level;
}

void Level::render(sf::RenderWindow & window)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			sf::Sprite s(textures[map[i][j].getImgNum()]);
			s.setPosition(sf::Vector2f(i * 64, j * 64));
			window.draw(s);
		}
	}
}

void Level::setName(string name)
{
	Level::name = name;
}