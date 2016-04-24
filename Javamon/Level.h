#pragma once
#include <string>

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <fstream>
#include <SFML/System/String.hpp>
#include <vector>

#include "Variables.h"
#include "Math.h"
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
	/*
	Enum to let super-class (SINGLEPLAYER) know what level wants it to do
	*/
	enum RequestMode{MAIN_MENU, NONE};
	/*
	Returns a command that level wants the super class to do
	*/
	RequestMode getRequestedMode() { return rm; }
	/*
	Lets the level know that the super-class has read its request
	*/
	void setRequestedModeRead() { rm = RequestMode::NONE; }

	/*
	Default Constructor
	*/
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
	Not implemented
	*/
	Level(sf::String, sf::String, sf::String);
	
	/*
	For multiplayer mode, so that the server can add a player to a preëxisting level.
	*/
	void addPlayer(Player p);

	~Level();

	void update(Controls&, int);
	void render(sf::RenderWindow&, KText &, int);

	/*
	Returns a boolean that tells the (faux)listener that another level needs to be loaded.
	This method is okay for single player, but we need something else for multiplayer.
	*/
	bool isRequestingLevelChange();
	/*
	This allows the faux-level listener to get the new level name and and player so that it
	can instantiate another level
	*/
	void getPlayer(Player&, sf::String&);

	/*
	Scans to see if a player is under a player so that his sprite draw order can be changed.
	*/
	bool isPlayerUnderNPC(int playerNumber);

	sf::String getAuth() { return auth; }
	sf::String getPack() { return pack; }
	sf::String getName() { return name; }

	/*Because level isn't a screen, we need another duplicate enum called mode for loading purposes*/
	static enum Mode { REG = 0, LOADING = 1 };
	Level::Mode getMode();

	/*Self explanitory, idk if it is used although*/
	void setLanguageOfPlayer(int num, Language l) { players[num].setLanguage(l); }
private:
	int height;
	int width;

	RequestMode rm;

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

	Level::Mode mode = Mode::LOADING;

	vector<Word> names;
	int spawnX;
	int spawnY;
	Direction spawnDirection;
	Tile** map;

	vector<Tile> transparentOverhangTiles;
	vector<Tile> opaqueOverhangTiles;

	vector<Teleport> teleports;	//List of teleporters
	
	vector<sf::Texture> textures;
	vector<sf::Texture> dialogBoxes;

	int dialogNPCNum;

	vector<Player> players;
	vector<NPC> npcs;

	void loadLevel(sf::String, sf::String, sf::String);

	/*We need to account for multiple characters leaving a stage in the same update frame*/
	bool requestsLevelChange = false;

	Player player;
	sf::String toLevel;
	void requestLevelChange(int, sf::String);
};