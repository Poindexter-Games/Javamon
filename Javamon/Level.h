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
#include "Events.h"

using namespace std;

class Level
{
private:
	Events eventListener;

	string auth; //This is generally the author of the packs' name
	string pack; //This is the individual pack name
	string name; //This is the name for programming purposes, not the user display name

	string dispName; //This is the user friendly name

	Tile **map;
	Teleport *teleports; //List of teleports
	int width;
	int height;

	sf::Image textureMap;
	sf::Texture* textures;

	sf::Image costumeMap;
	sf::Texture* costumes;

	Player p;
public:
	Level(Events&);
	Level(string); //Test method
	Level(string, string, string); //Regular way to load level, unimplemented, use the test method

	void update(bool*);
	void render(sf::RenderWindow&);

	void setName(string);

	string getAuth(){return auth;}
	string getPack(){return pack;}
	string getName(){return name;}

};