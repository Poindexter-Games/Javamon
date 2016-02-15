#include "Level.h"

using namespace std;

Level::Level()
{
	//loadLevel(L"Poindexter", L"Error", L"Error");
}

Level::Level(sf::String auth, sf::String pack, sf::String level, int dummyVariable)
{
	loadLevel(auth, pack, level);
	Player p;
	p.place(spawnX, spawnY, spawnDirection);
	players.push_back(p);
}

Level::Level(sf::String auth, sf::String pack, sf::String level, Player p)
{
	loadLevel(auth, pack, level);
	players.push_back(p);
}

void Level::loadLevel(sf::String auth, sf::String pack, sf::String name)
{
	requestsLevelChange = false;
	Level::auth = auth;
	Level::pack = pack;
	Level::name = name;

	KFile file(PACKS + auth + L"/" + pack + L"/" + name + L"/Level.txt");

	int width = 0;
	int height = 0;
	bool widthLoaded = false;
	bool heightLoaded = false;
	bool mapLoaded = false;

	bool spawnStuffLoaded = false;

	sf::String* segments;
	int length;

	for (bool b = true; b; )
	{
		file.readLine(segments, length);

		if (length == 0) continue;

		//for (int i = 0; i < length; i++)
		//{
		//	StringEditor::echo(segments[i]);
		//}

		if (length == 2)
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

		if (length == 4)
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
			}
		}

		if (length == 5)
		{
			if (StringEditor::equals(segments[0], L"setRow"))
			{
				for (int i = 0; i < map.size(); i++)
				{
					map[i][stoi(segments[1].toWideString())] = Tile(stoi(segments[2].toWideString()), stoi(segments[3].toWideString()), stoi(segments[4].toWideString()));
				}
			}
			if (StringEditor::equals(segments[0], L"setCol"))
			{
				for (int i = 0; i < map[stoi(segments[1].toWideString())].size(); i++)
				{
					map[stoi(segments[1].toWideString())][i] = Tile(stoi(segments[2].toWideString()), stoi(segments[3].toWideString()), stoi(segments[4].toWideString()));
				}
			}
		}

		if (length == 6)
		{
			if (StringEditor::equals(segments[0], L"setBlock"))
			{
				map[stoi(segments[1].toWideString())][stoi(segments[2].toWideString())] = Tile(stoi(segments[3].toWideString()), stoi(segments[4].toWideString()), stoi(segments[5].toWideString()));
			}
		}

		if (length == 9)
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

	sf::Image blockSheet;
	blockSheet.loadFromFile(PACKS + auth + L"/" + pack + L"/" + name + L"/Spritesheet.png");
	StringEditor::echo(sf::String(PACKS + auth + L"/" + pack + L"/" + name + L"/Spritesheet.png").toWideString());

	textures.resize(256);
	for (int i = 0; i < 256; i++)
	{
		textures[i].loadFromImage(blockSheet, sf::IntRect((i % 16) * BLOCK_SIZE, (int)(i / 16) * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE));
	}
}

void Level::requestLevelChange(int playerNumber, sf::String toLevel)
{
	StringEditor::echo(L"Level requested change.");

	requestsLevelChange = true;
	Level::toLevel = toLevel;
	player = players[playerNumber];
	players.erase(players.begin() + playerNumber);
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

			/*
			TODO NPC Check
			*/

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

void Level::render(sf::RenderWindow & window, int playerNumber)
{
	//Set the view
	sf::View view;
	view.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	view.setCenter(sf::Vector2f(players[playerNumber].getActualX() + 32, players[playerNumber].getActualY() + 32));
	window.setView(view);

	//Draw blocks
	for (int x = 0; x < map.size(); x++)
	{
		for (int y = 0; y < map[x].size(); y++)
		{
			sf::Sprite s(textures[map[x][y].getImgNum()]);
			s.setPosition(sf::Vector2f((float)x * BLOCK_SIZE, (float)y * BLOCK_SIZE));
			window.draw(s);
		}
	}
	//Draw character if above NPC
	players[playerNumber].render(window);

	//DRAW NPCs
	
	/*
	TODO Draw NPCs
	*/

	//Draw character if below npc
	players[playerNumber].render(window);

	/*if (mode == Mode::DIALOG)
	{
		drawDialog(window, font);
	}*/
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
