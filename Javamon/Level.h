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
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/String.hpp>

#include "Variables.h"
#include "StringEditor.h"
#include "Controls.h"
#include "KText.h"
#include "Teleport.h"
#include "Tile.h"
#include "Player.h"

using namespace std;

class Level
{
private:
	/*
	Mode is going to be moved into the player class soon so not every player
	in a level forced into dialog mode when one player reads/talks to something
	*/
	enum Mode {REG, DIALOG};
	Mode mode;

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

	Tile **map;
	int width;
	int height;
	int spawnX;
	int spawnY;
	Direction spawnDirection;

	Teleport *teleports;	//List of teleports
	int numTeleports;		//Number of teleports

	Player* npcs;
	int numNPCs;

	sf::Image textureMap;
	sf::Texture* textures;

	sf::Image costumeMap;
	sf::Texture* costumes;

	sf::Texture dialogBox;
	int dialogNPCNum;

	Player p;

	bool levelRequestsChange;
	bool levelRequestsBattle;
	sf::String toLevelName;
	int toLevelX;
	int toLevelY;
	Direction toLevelDirection;

	/*
	Contains methods shared by both constructors
	*/
	void loadLevel(Language, wstring, wstring, wstring);
public:
	/*
	Constructor for initializing the level
	*/
	Level(Language, wstring, wstring, wstring);
	/*
	Constructor for initializing the level with certain player properties
	This method will be depreciated soon because instantiating levels
	with player properties is bad
	*/
	Level(Language, wstring, wstring, wstring, int, int, Direction);

	void update(Controls&);
	void render(sf::RenderWindow&, KText&);
	void drawDialog(sf::RenderWindow&, KText&);

	sf::String getAuth(){return auth;}
	sf::String getPack(){return pack;}
	sf::String getName(){return name;}

	bool isRequestingLevelChange() { return levelRequestsChange; }
	void requestLevelChange(wstring, int, int, Direction);

	sf::String	getToLevelName()		{ return toLevelName; }
	int			getToLevelX()			{ return toLevelX; }
	int			getToLevelY()			{ return toLevelY; }
	Direction	getToLevelDirection()	{ return toLevelDirection; }


	bool isRequestingBattleScreen() { return levelRequestsBattle; }
	void requestBattleScreen();

	bool ifPlayerIsUnderNPC();
	void drawPlayer(sf::RenderWindow&);
};