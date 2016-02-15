#pragma once
#include <string>

#include <SFML/Graphics/Image.hpp>
#include <cstdint>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <iostream>
#include <fstream>
#include <SFML/System/String.hpp>
#include <vector>

#include "Variables.h"
#include "StringEditor.h"
#include "Controls.h"
#include "KText.h"
#include "Teleport.h"
#include "Tile.h"
#include "Player.h"
#include "NPC.h"

class Level
{
public:
	Level();
	/*
	Constuctor for 1 player mode with loading character from save file
	The int is a dummy variable
	*/
	Level(sf::String, sf::String, sf::String, int);
	/*
	Standard Constructor for 1 player mode
	*/
	Level(sf::String, sf::String, sf::String, Player);

	/*
	Standard constructor for multiplayer mode
	*/
	Level(sf::String, sf::String, sf::String);

	/*
	TODO
	*/
	//void addPlayer(Player p);

	~Level();

	void update(Controls&, int);
	void render(sf::RenderWindow&, int);

	bool isRequestingLevelChange();
	void getPlayer(Player&, sf::String&);

	sf::String getAuth() { return auth; }
	sf::String getPack() { return pack; }
	sf::String getName() { return name; }

	static enum Mode { REG = 0, LOADING = 1 };
	Level::Mode getMode();
private:

	/*
	Author is the subfolder under Resources/Packs/
	This is generally named after the author of the pack
	*/
	sf::String auth;

	/*
	Pack is the subfolder folder under Resources/Packs/%auth%
	This is generally named after the pack (mod)
	*/
	sf::String pack;

	/*
	This is the subfolder under Resources/Packs/%auth%/%pack%
	This is not the name used for the level switch sign
	*/
	sf::String name;

	/*
	This is the language friendly name for in-game mentions of the level
	*/
	sf::String dispName;

	Level::Mode mode = Mode::LOADING;

	vector<vector<Tile>> map;
	int spawnX;
	int spawnY;
	Direction spawnDirection;

	vector<Teleport> teleports;	//List of teleports
	
	vector<sf::Texture> textures;

	int dialogNPCNum;

	vector<Player> players;
	vector<NPC> npcs;

	void loadLevel(sf::String, sf::String, sf::String);

	bool requestsLevelChange = false;
	Player player;
	sf::String toLevel;
	void requestLevelChange(int, sf::String);
};