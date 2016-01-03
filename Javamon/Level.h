#pragma once
#include <string>
#include "Tile.h"
#include <SFML/Graphics/Image.hpp>
#include <cstdint>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <iostream>
#include "Player.h"

using namespace std;

class Level
{
private:
	string pack;
	string name; //This is the name for programming purposes, not the user display name
	Tile **map;
	int width;
	int height;

	sf::Image textureMap;
	sf::Texture* textures;

	sf::Image costumeMap;
	sf::Texture* costumes;

	Player p;
public:
	Level();
	Level(string); //Test method
	Level(string, string); //Regular way to load level, unimplemented, use the test method

	void update(bool*);
	void render(sf::RenderWindow&);

	void setName(string);

	string getName(){return name;}

};