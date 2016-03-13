#include "Level.h"

Level::Level()
{
	mode == Mode::LOADING;
	//loadLevel(L"Poindexter", L"Error", L"Error");
}

Level::Level(sf::String auth, sf::String pack, sf::String level, int dummyVariable)
{
	mode == Mode::LOADING;

	loadLevel(auth, pack, level);
	Player p;
	p.place(spawnX, spawnY, spawnDirection);
	players.push_back(p);

	mode = Mode::REG;
}

Level::Level(sf::String auth, sf::String pack, sf::String level, Player p)
{
	mode == Mode::LOADING;

	loadLevel(auth, pack, level);
	players.push_back(p);

	mode = Mode::REG;
}

void Level::loadLevel(sf::String auth, sf::String pack, sf::String name)
{
	requestsLevelChange = false;
	Level::auth = auth;
	Level::pack = pack;
	Level::name = name;

	Word codeName;
	codeName.langCode = sf::String(L"code_CODE");
	codeName.str = name;
	names.push_back(codeName);

	KFile file(PACKS + auth + L"/" + pack + L"/" + name + L"/Level.txt");

	int width = 0;				//Temporary variable to store the width of the level
	int height = 0;				//Temporary variable to store the height of the level
	bool widthLoaded = false;
	bool heightLoaded = false;
	bool mapLoaded = false;		//Flag which is true if the map dimensions were loaded
	int numNPC = -1;			//Counts the index number of each npc instantiated, is -1 if none are instantiated (I forgot the reasoning behind this...)

	bool spawnStuffLoaded = false;	//Flag which is true if the spawn coordinates were loaded

	bool comment = false;	//Flag which states if reading a multiline comment
	sf::String* segments;	//Broken apart parameters
	int length;				//Number of parameters

	for (bool b = true; b; )
	{
		file.readLine(segments, length);

		//Conditions for not reading a line
		if (length == 0) continue;
		if (StringEditor::equals(segments[0], L"endComment"))
		{
			comment = false;
			continue;
		}
		if (comment == true) continue;

		//Output the split segments to the console
		for (int i = 0; i < length; i++)
		{
			StringEditor::echo(segments[i]);
		}

		if (length == 1)
		{
			if (StringEditor::equals(segments[0], L"addNPC"))
			{
				numNPC++;
				npcs.push_back(NPC());
				npcs[numNPC].loadTextures(auth, pack, name, 0);
				npcs[numNPC].loadFromFile(file, auth, pack, name);
			}
			else if (StringEditor::equals(segments[0], L"beginComment"))
			{
				comment = true;
				continue;
			}
		}

		else if (length == 2)
		{
			if (StringEditor::equals(segments[0], L"setWidth"))
			{
				width = stoi(segments[1].toWideString());
				widthLoaded = true;
			}
			else if (StringEditor::equals(segments[0], L"setHeight"))
			{
				height = stoi(segments[1].toWideString());
				heightLoaded = true;
			}
		}

		else if (length == 3)
		{
			if (StringEditor::equals(segments[0], L"setName"))
			{
				Word s_name;
				s_name.langCode = segments[1];
				s_name.str = segments[2];
				names.push_back(s_name);
				continue;
			}
		}

		else if (length == 4)
		{
			if (StringEditor::equals(segments[0], L"setSpawn"))
			{
				spawnX = stoi(segments[1].toWideString());
				spawnY = stoi(segments[2].toWideString());
				int d = 0;
				if (StringEditor::equals(segments[3], L"UP"))
				{
					d = 0;
				}
				if (StringEditor::equals(segments[3], L"LEFT"))
				{
					d = 1;
				}
				if (StringEditor::equals(segments[3], L"DOWN"))
				{
					d = 2;
				}
				else
				{
					d = 3;
				}
				spawnDirection = to_Direction(d);
				spawnStuffLoaded = true;
				continue;
			}
		}

		else if (length == 5)
		{
			if (StringEditor::equals(segments[0], L"setRow"))
			{
				for (int i = 0; i < map.size(); i++)
				{
					map[i][stoi(segments[1].toWideString())] = Tile(stoi(segments[2].toWideString()), stoi(segments[3].toWideString()), stoi(segments[4].toWideString()));
				}
				continue;
			}
			else if (StringEditor::equals(segments[0], L"setCol"))
			{
				for (int i = 0; i < map[stoi(segments[1].toWideString())].size(); i++)
				{
					map[stoi(segments[1].toWideString())][i] = Tile(stoi(segments[2].toWideString()), stoi(segments[3].toWideString()), stoi(segments[4].toWideString()));
				}
				continue;
			}
		}

		else if (length == 6)
		{
			if (StringEditor::equals(segments[0], L"setBlock"))
			{
				map[stoi(segments[1].toWideString())][stoi(segments[2].toWideString())] = Tile(stoi(segments[3].toWideString()), stoi(segments[4].toWideString()), stoi(segments[5].toWideString()));
				continue;
			}
		}

		else if (length == 8)
		{
			if (StringEditor::equals(segments[0], L"setArea"))
			{
				int tempX = stoi(segments[1].toWideString());
				int tempY = stoi(segments[2].toWideString());
				int tempToX = stoi(segments[3].toWideString());
				int tempToY = stoi(segments[4].toWideString());

				for (int i = tempX; i <= tempToX; i++)
				{
					for (int j = tempY; j <= tempToY; j++)
					{
						map[i][j] = Tile(stoi(segments[5].toWideString()), stoi(segments[6].toWideString()), stoi(segments[7].toWideString()));
					}
				}
				continue;
			}
			else if (StringEditor::equals(segments[0], L"setDefinedArea"))
			{
				int tempX = stoi(segments[1].toWideString());
				int tempY = stoi(segments[2].toWideString());
				int tempToX = stoi(segments[3].toWideString());
				int tempToY = stoi(segments[4].toWideString());

				for (int i = tempX; i <= tempToX; i++)
				{
					for (int j = tempY; j <= tempToY; j++)
					{
						int xOffset = i - tempX;
						int yOffset = j - tempY;

						//The 16 is the width of the sprite sheet
						map[i][j] = Tile(stoi(segments[5].toWideString()) + xOffset + (16 * yOffset), stoi(segments[6].toWideString()), stoi(segments[7].toWideString()));
					}
				}
				continue;
			}
		}

		else if (length == 9)
		{
			if (StringEditor::equals(segments[0], L"addTeleport"))
			{
				int d = 0;
				if (StringEditor::equals(segments[6], L"UP"))
				{
					d = 0;
				}
				else if (StringEditor::equals(segments[6], L"LEFT"))
				{
					d = 1;
				}
				else if (StringEditor::equals(segments[6], L"DOWN"))
				{
					d = 2;
				}
				else
				{
					d = 3;
				}
				float f = -1;
				if (StringEditor::equals(segments[8], L"SHALLOW"))
				{
					f = .25f;
				}
				else
				{
					f = .5f;
				}
				Teleport t(stoi(segments[1].toWideString()), stoi(segments[2].toWideString()), segments[3], stoi(segments[4].toWideString()), stoi(segments[5].toWideString()), to_Direction(d), stoi(segments[7].toWideString()), f);
				teleports.push_back(t);
				continue;
			}
		}

		if (!mapLoaded && widthLoaded && heightLoaded)
		{
			map.resize(width);
			for (int x = 0; x < width; x++)
			{
				map[x].resize(height);
			}

			mapLoaded = true;
		}

		if (segments[0].toWideString().compare(L"endFile") == 0)
		{
			b = false;
		}
	}
	file.close();

	//Creating temp map if something wasn't loaded
	//If there was an error in the file, the program most likely won't make it this far into the code.

	if (!mapLoaded)
	{
		width = 1;
		height = 1;
		
		map.resize(width);
		for (int x = 0; x < width; x++)
		{
			map[x].resize(height);
		}
	}
	if (!spawnStuffLoaded)
	{
		spawnX = 0;
		spawnY = 0;
		spawnDirection = Direction::RIGHT;
	}

	//Loading block textures

	sf::Image blockSheet;
	blockSheet.loadFromFile(PACKS + auth + L"/" + pack + L"/" + name + L"/Spritesheet.png");
	StringEditor::echo(sf::String(PACKS + auth + L"/" + pack + L"/" + name + L"/Spritesheet.png").toWideString());

	textures.resize(256);
	for (int i = 0; i < 256; i++)
	{
		textures[i].loadFromImage(blockSheet, sf::IntRect((i % 16) * BLOCK_SIZE, (int)(i / 16) * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE));
	}

	//Loading Dialog Boxes

	sf::Image dialogBoxImg;
	if (!dialogBoxImg.loadFromFile(VIDEO + L"DialogBox.png"))
	{
		StringEditor::echo(L"Dialog Box was not loaded");
	}
	dialogBoxes.push_back(sf::Texture());
	dialogBoxes[0].loadFromImage(dialogBoxImg, sf::IntRect(0, 0, 1280, 200));
}

void Level::requestLevelChange(int playerNumber, sf::String toLevel)
{
	mode = Level::Mode::LOADING;
	Level::toLevel = toLevel;
	player = players[playerNumber];
	players.erase(players.begin() + playerNumber);
	requestsLevelChange = true;
}

Level::Mode Level::getMode()
{
	return mode;
}

Level::~Level()
{
	//delete[] map;
	//delete[] teleports;
	//delete[] npcs;
	//delete[] textures;
	//delete[] costumes;
}

void Level::update(Controls & c, int playerNumber)
{
	if (players[playerNumber].getMode() == Player::Mode::DIALOG)
	{
		if (c.isPressedForFirstTime(Control::ACCEPT))
		{
			players[playerNumber].setNPCDialogNumber(-1);
			players[playerNumber].setMode(Player::Mode::NORMAL);
		}
		return;
	}
	if (players[playerNumber].getMode() == Player::Mode::MENU)
	{
		if (c.isPressedForFirstTime(Control::CANCEL))
		{
			players[playerNumber].setMode(Player::Mode::NORMAL);
		}
		else if (c.isPressedForFirstTime(Control::START))
		{
			players[playerNumber].setMode(Player::Mode::NORMAL);
		}
		return;
	}

	if (!players[playerNumber].isLocked())
	{
		//If player is in transition between two blocks
		int time = c.getTimePressed(players[playerNumber].getDirection());
		time = ((time - (time % 15)) / 15) % 4;
		if (time == 3)time = 1;
		players[playerNumber].setAnimationFrame(time + 1);

		if (players[playerNumber].getActualY() - 4.0f>(float)players[playerNumber].getY() * BLOCK_SIZE) players[playerNumber].adjustActualY(-4.0f);
		else if ((int)players[playerNumber].getActualY() > players[playerNumber].getY() * BLOCK_SIZE) players[playerNumber].setActualY((float)players[playerNumber].getY() * BLOCK_SIZE);

		if (players[playerNumber].getActualX() - 4.0f>(float)players[playerNumber].getX() * BLOCK_SIZE) players[playerNumber].adjustActualX(-4.0f);
		else if ((int)players[playerNumber].getActualX()>players[playerNumber].getX() * BLOCK_SIZE) players[playerNumber].setActualX((float)players[playerNumber].getX() * BLOCK_SIZE);

		if (players[playerNumber].getActualY() + 4.0f<(float)players[playerNumber].getY() * BLOCK_SIZE) players[playerNumber].adjustActualY(4.0f);
		else if ((int)players[playerNumber].getActualY()<players[playerNumber].getY() * BLOCK_SIZE) players[playerNumber].setActualY((float)players[playerNumber].getY() * BLOCK_SIZE);

		if (players[playerNumber].getActualX() + 4.0f < (float)players[playerNumber].getX() * BLOCK_SIZE) players[playerNumber].adjustActualX(4.0f);
		else if ((int)players[playerNumber].getActualX()<players[playerNumber].getX() * BLOCK_SIZE) players[playerNumber].setActualX((float)players[playerNumber].getX() * BLOCK_SIZE);
	}
	else if (players[playerNumber].isLocked() && c.isOnlyOneDirectionHeldDown() && players[playerNumber].getZDirection() == 0)
	{
		//If player is not moving and wants to move

		//Player has held down long enough to move
		if (c.getTimePressed(players[playerNumber].getDirection()) >= 4)
		{
			bool upBlocked = false;
			bool leftBlocked = false;
			bool downBlocked = false;
			bool rightBlocked = false;

			//keep player from leaving the boundaries
			if (players[playerNumber].getY() == 0) { upBlocked = true; }
			if (players[playerNumber].getX() == 0) { leftBlocked = true; }
			if ((players[playerNumber].getY() == (map[0].size() - 1))) { downBlocked = true; }
			if ((players[playerNumber].getX() == (map.size() - 1))) { rightBlocked = true; }

			//npc collision
			for (int i = 0; i < npcs.size(); i++)
			{
				if (!upBlocked && players[playerNumber].getX() == npcs[i].getX() && players[playerNumber].getY() - 1 == npcs[i].getY())
				{
					upBlocked = true;
				}
				if (!leftBlocked && players[playerNumber].getX() - 1 == npcs[i].getX() && players[playerNumber].getY() == npcs[i].getY())
				{
					leftBlocked = true;
				}
				if (!downBlocked && players[playerNumber].getX() == npcs[i].getX() && players[playerNumber].getY() + 1 == npcs[i].getY())
				{
					downBlocked = true;
				}
				if (!rightBlocked && players[playerNumber].getX() + 1 == npcs[i].getX() && players[playerNumber].getY() == npcs[i].getY())
				{
					rightBlocked = true;
				}
			}

			//Final movement validity check
			if (players[playerNumber].getDirection() == Direction::UP)
			{
				if (!upBlocked && Tile::movementValid(map[players[playerNumber].getX()][players[playerNumber].getY()], map[players[playerNumber].getX()][players[playerNumber].getY() - 1]))
				{
					players[playerNumber].setY(players[playerNumber].getY() - 1);
					players[playerNumber].adjustActualY(-4.0f);
				}
			}
			else if (players[playerNumber].getDirection() == Direction::LEFT)
			{
				if (!leftBlocked && Tile::movementValid(map[players[playerNumber].getX()][players[playerNumber].getY()], map[players[playerNumber].getX() - 1][players[playerNumber].getY()]))
				{
					players[playerNumber].setX(players[playerNumber].getX() - 1);
					players[playerNumber].adjustActualX(-4.0f);
				}
			}
			else if (players[playerNumber].getDirection() == Direction::DOWN)
			{
				if (!downBlocked && Tile::movementValid(map[players[playerNumber].getX()][players[playerNumber].getY()], map[players[playerNumber].getX()][players[playerNumber].getY() + 1]))
				{
					players[playerNumber].setY(players[playerNumber].getY() + 1);
					players[playerNumber].adjustActualY(4.0f);
				}
			}
			else if (players[playerNumber].getDirection() == Direction::RIGHT)
			{
				if (!rightBlocked && Tile::movementValid(map[players[playerNumber].getX()][players[playerNumber].getY()], map[players[playerNumber].getX() + 1][players[playerNumber].getY()]))
				{
					players[playerNumber].setX(players[playerNumber].getX() + 1);
					players[playerNumber].adjustActualX(4.0f);
				}
			}
		}
		else
		{
			//Player hasn't held the button down for long enough so we should just change their direction
			players[playerNumber].setDirection(c.getOnlyDirectionHeldDown());
		}
	}
	else if (players[playerNumber].isLocked() && !c.isOnlyOneDirectionHeldDown())
	{
		//If player is not moving and does not want to move
		players[playerNumber].setAnimationFrame(0);
	
		if (c.isPressedForFirstTime(Control::ACCEPT))
		{
			Direction d = players[playerNumber].getDirection();
			for (int i = 0; i < npcs.size(); i++)
			{

				if (d == Direction::UP && players[playerNumber].getX() == npcs[i].getX() && players[playerNumber].getY() - 1 == npcs[i].getY())
				{
					players[playerNumber].setNPCDialogNumber(i);
					players[playerNumber].setMode(Player::Mode::DIALOG);
				}
				else if (d == Direction::LEFT && players[playerNumber].getX() - 1 == npcs[i].getX() && players[playerNumber].getY() == npcs[i].getY())
				{
					players[playerNumber].setNPCDialogNumber(i);
					players[playerNumber].setMode(Player::Mode::DIALOG);
				}
				else if (d == Direction::DOWN && players[playerNumber].getX() == npcs[i].getX() && players[playerNumber].getY() + 1 == npcs[i].getY())
				{
					players[playerNumber].setNPCDialogNumber(i);
					players[playerNumber].setMode(Player::Mode::DIALOG);
				}
				else if (players[playerNumber].getX() + 1 == npcs[i].getX() && players[playerNumber].getY() == npcs[i].getY())
				{
					players[playerNumber].setNPCDialogNumber(i);
					players[playerNumber].setMode(Player::Mode::DIALOG);
				}
			}
		}
		else if (c.isPressedForFirstTime(Control::START))
		{
			players[playerNumber].setMode(Player::Mode::MENU);
		}
	}
	if (players[playerNumber].isLocked())
	{
		for (int i = 0; i < teleports.size(); i++)
		{
			if (players[playerNumber].getX() == teleports[i].getX() && players[playerNumber].getY() == teleports[i].getY())
			{
				if (players[playerNumber].getSteepness() == .25f)
				{
					players[playerNumber].setSteepness(.5f);
				}
				else
				{
					players[playerNumber].setSteepness(.25f);
				}

				if (teleports[i].intraLevel())
				{
					players[playerNumber].place(teleports[i].getToX(), teleports[i].getToY(), teleports[i].getDirection());
				}
				if (teleports[i].interLevel())
				{
					players[playerNumber].place(teleports[i].getToX(), teleports[i].getToY(), teleports[i].getDirection(), players[playerNumber].getZDirection(), players[playerNumber].getSteepness());
					requestLevelChange(playerNumber, teleports[i].getName());
					return;
				}
			}
		}
	}

	//The next code is to detect if the player is moving onto a teleport, and if he is, start displaying the going up or down animation if it is needed
	players[playerNumber].setZDirection(0);
	players[playerNumber].setSteepness(0.0f);
	for (int i = 0; i < teleports.size(); i++)
	{
		if (players[playerNumber].getX() == teleports[i].getX() && players[playerNumber].getY() == teleports[i].getY())
		{
			players[playerNumber].setZDirection(teleports[i].getZDirection());
			players[playerNumber].setSteepness(teleports[i].getSteepness());
		}
	}
}

void Level::render(sf::RenderWindow & window, KText & font, int playerNumber)
{
	if (mode == Level::Mode::LOADING)
		return;
	if (playerNumber >= players.size())
		return;

	//Set the view
	sf::View view;
	view.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	view.setCenter(sf::Vector2f(players[playerNumber].getActualX() + 32, players[playerNumber].getActualY() + 32));
	window.setView(view);

	//Draw blocks
	for (int x = 0; x < map.size(); x++)
	{
		if (x >= players[playerNumber].getX() - 11 && x <= players[playerNumber].getX() + 11)
		{
			for (int y = 0; y < map[x].size(); y++)
			{
				if (y >= players[playerNumber].getY() - 7 && y <= players[playerNumber].getY() + 6)
				{
					sf::Sprite s(textures[map[x][y].getImgNum()]);
					s.setPosition(sf::Vector2f((float)x * BLOCK_SIZE, (float)y * BLOCK_SIZE));
					window.draw(s);
				}
			}
		}
		
	}
	if (!isPlayerUnderNPC(playerNumber))
	{
		players[playerNumber].render(window);
	}

	//DRAW NPCs
	
	for (int i = 0; i < npcs.size(); i++)
	{
		npcs[i].render(window);
	}

	//Draw character if below npc
	if (isPlayerUnderNPC(playerNumber))
	{
		players[playerNumber].render(window);
	}

	if (players[playerNumber].getMode() == Player::Mode::DIALOG)
	{
		sf::View view;
		view.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		view.setCenter(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
		window.setView(view);

		sf::Sprite s(dialogBoxes[0]);	//TODO Multiple types of dialog boxes
		s.setPosition(sf::Vector2f(0, DIALOG_BOX_LOW));
		window.draw(s);
		font.drawText(window, 16, DIALOG_BOX_LOW + 16, npcs[players[playerNumber].getNPCDialogNumber()].getDialog(players[playerNumber].getLanguageCode()));
	}

	for (int i = 0; i < floatingTiles.size(); i++)
	{
		if (i >= players[playerNumber].getY() - 7 && i <= players[playerNumber].getY() + 6)
		{
			sf::View view;
			view.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
			view.setCenter(sf::Vector2f(players[playerNumber].getActualX() + 32, players[playerNumber].getActualY() + 32));
			window.setView(view);

			sf::Sprite s(textures[floatingTiles[i].getImgNum()]);
			s.setPosition(sf::Vector2f(floatingTiles[i].getX() * BLOCK_SIZE, floatingTiles[i].getY() * BLOCK_SIZE));
			window.draw(s);
		}
	}

	if (players[playerNumber].getMode() == Player::Mode::MENU)
	{
		player.renderMenu(window);
	}

	//RENDER DEBUG STUFF
	font.coordinates(window, players[playerNumber].getX(), players[playerNumber].getY());
}

bool Level::isRequestingLevelChange()
{
	return requestsLevelChange;
}

void Level::getPlayer(Player & p, sf::String & s)
{
	p = player;
	s = toLevel;
}

bool Level::isPlayerUnderNPC(int playerNumber)
{
	Player p = players[playerNumber];
	if (players[playerNumber].getY() == 0)
	{
		return false;
	}
	for (int i = 0; i < npcs.size(); i++)
	{
		if (npcs[i].getX() == p.getX() && npcs[i].getY() == p.getY() - 1)
		{
			return true;
		}
		if (npcs[i].getX() == p.getX() - 1 && npcs[i].getY() == p.getY() - 1)
		{
			return true;
		}
		if (npcs[i].getX() == p.getX() + 1 && npcs[i].getY() == p.getY() - 1)
		{
			return true;
		}
	}
	return false;
}