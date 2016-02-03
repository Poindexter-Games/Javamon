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
	enum Mode {REG, DIALOG};
	Mode mode;

	sf::String auth; //This is generally the author of the packs' name
	sf::String pack; //This is the individual pack name
	sf::String name; //This is the name for programming purposes, not the user display name

	sf::String dispName; //This is the user friendly name

	Tile **map;
	int width;
	int height;

	Teleport *teleports; //List of teleports
	int numTeleports; //Number of teleports

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

	void loadLevel(Language, wstring, wstring, wstring); //methods that are shared by the constructor that creates the level from scratch and the one that creates a level from another level
public:
	Level(Language, wstring, wstring, wstring); //Regular way to load level, unimplemented, use the test method
	Level(Language, wstring, wstring, wstring, int, int, Direction); //Regular way to load a level but by teleports

	void update(Controls&);
	void render(sf::RenderWindow&, KText&);
	void drawDialog(sf::RenderWindow&, KText&);

	sf::String getAuth(){return auth;}
	sf::String getPack(){return pack;}
	sf::String getName(){return name;}

	bool isRequestingLevelChange() { return levelRequestsChange; }
	void requestLevelChange(wstring, int, int, Direction);

	sf::String getToLevelName() { return toLevelName; }
	int getToLevelX() { return toLevelX; }
	int getToLevelY() { return toLevelY; }
	Direction getToLevelDirection() { return toLevelDirection; }


	bool isRequestingBattleScreen() { return levelRequestsBattle; }
	void requestBattleScreen();

	bool ifPlayerIsUnderNPC();
	void drawPlayer(sf::RenderWindow&);
};