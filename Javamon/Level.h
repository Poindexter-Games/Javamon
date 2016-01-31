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

	string auth; //This is generally the author of the packs' name
	string pack; //This is the individual pack name
	string name; //This is the name for programming purposes, not the user display name

	wstring dispName; //This is the user friendly name

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
	string toLevelName;
	int toLevelX;
	int toLevelY;
	int toLevelDirection;
public:
	Level();
	Level(int, int, int, int); //Testing Constructor
	Level(string, string, string); //Regular way to load level, unimplemented, use the test method

	void newLevel(int, int, int, int);

	void update(Controls&);
	void render(sf::RenderWindow&, KText&);
	void drawDialog(sf::RenderWindow&, KText&);

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


	bool isRequestingBattleScreen() { return levelRequestsBattle; }
	void requestBattleScreen();

	bool ifPlayerIsUnderNPC()
	{
		if (p.getBlockY() == 0)
		{
			return false;
		}
<<<<<<< HEAD
		for (int i = 0; i < numNPCs; i++)
=======
		for (int i = 0; i < numNPCS; i++)
>>>>>>> origin/master
		{
			if (npcs[i].getBlockX() == p.getBlockX() && npcs[i].getBlockY() == p.getBlockY() - 1)
			{
				return true;
			}
			if (npcs[i].getBlockX() == p.getBlockX() - 1 && npcs[i].getBlockY() == p.getBlockY() - 1)
			{
				return true;
			}
			if (npcs[i].getBlockX() == p.getBlockX() + 1 && npcs[i].getBlockY() == p.getBlockY() - 1)
			{
				return true;
			}
		}
		return false;
	}
	void drawPlayer(sf::RenderWindow&);
};