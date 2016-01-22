#pragma once
#include <string>

#include <SFML/Graphics/Image.hpp>
#include <codecvt> //This is for reading UTF-8 Files [?]
#include <cstdint>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <iostream>
#include <fstream>

#include "Teleport.h"
#include "Tile.h"
#include "Player.h"

using namespace std;

class Level
{
private:
	int BLOCK_SIZE = 64; //This is a constant value that states the size of blocks, this will be useful if we program for higher resolutions

	string auth; //This is generally the author of the packs' name
	string pack; //This is the individual pack name
	string name; //This is the name for programming purposes, not the user display name

	string dispName; //This is the user friendly name

	Tile **map;
	Teleport *teleports; //List of teleports
	int width;
	int height;
	int numTeleports; //Number of teleports

	sf::Image textureMap;
	sf::Texture* textures;

	sf::Image costumeMap;
	sf::Texture* costumes;

	Player p;

	bool levelRequestsChange;
	string toLevelName;
	int toLevelX;
	int toLevelY;
	int toLevelDirection;
public:
	Level();
	Level(int, int, int, int); //Test method
	Level(string, string, string); //Regular way to load level, unimplemented, use the test method

	void newLevel(int, int, int, int);

	void update(bool*);
	void render(sf::RenderWindow&);

	void setName(string);

	string getAuth(){return auth;}
	string getPack(){return pack;}
	string getName(){return name;}

	bool isRequestingLevelChange() { return levelRequestsChange; }
	void requestLevelChange(string, int, int, int);

	string getToLevelName() { return toLevelName; }
	int getToLevelX() { return toLevelX; }
	int getToLevelY() { return toLevelY; }
	int getToLevelDirection() { return toLevelDirection; }
};