#include "Level.h"

using namespace std;

Level::Level(Language l, wstring auth, wstring pack, wstring level)
{
	loadLevel(l, auth, pack, level);
	//Set the remaining stuff
	p.place(spawnX, spawnY, spawnDirection);
}

Level::Level(Language l, wstring auth, wstring pack, wstring level, int x, int y, Direction d)
{
	loadLevel(l, auth, pack, level);
	//Set the remaining stuff
	p.place(x, y, d);
}

void Level::loadLevel(Language l, wstring auth, wstring pack, wstring level)
{
	mode = Mode::REG;
	levelRequestsChange = false;
	levelRequestsBattle = false;
	dialogNPCNum = -1;

	Level::auth = auth;
	Level::pack = pack;
	Level::name = level;

	bool dispNameLoaded = false;
	bool widthLoaded = false;
	bool heightLoaded = false;
	bool spawnXLoaded = false;
	bool spawnYLoaded = false;
	bool spawnDirectionLoaded = false;
	bool mapCreated = false;
	bool npcsCreated = false;
	bool teleportsCreated = false;

	Level::p = Player();

	/*
	FileI is the Level.txt that the game is building the level from
	FileO is the Log.txt that the game is writing an error log to (once I implement it)
	*/

	locale locale("");					//This will read the user's locale, so the program can determine string encoding since wifstream uses a regular string to load a file
	string pathi = sf::String(RESOURCES + L"Packs/" + Level::auth + L"/" + pack + L"/" + level + L"/Level.txt").toAnsiString(locale);
	//string patho = sf::String(RESOURCES + L"Packs/" + Level::auth + L"/" + pack + L"/" + level +   L"/Log.txt").toAnsiString(locale);

	wifstream filei;
	filei.open(pathi);

	//wofstream fileo;
	//fileo.open(patho);

	wstring line;			//This is the file of the line
	getline(filei, line);	//This is to ignore the first line of the file, which contains the BOM character
	int paramNum;
	wstring* param;			//This is the wstring to hold what command/parameter is to be used

	for (bool b = true; b;)
	{
		StringEditor::echo(L"==========START OF LOOP ITERATION============");
		getline(filei, line);										//Get the line from the file
		paramNum = StringEditor::getNumberOfSegments(line);
		if (paramNum == 0) continue;								//This means the line was blank
		if (paramNum == -1) StringEditor::echo(L"ERROR: " + line);
		param = new wstring[paramNum];
		param = StringEditor::breakApart(line);

		for (int i = 0; i < paramNum; i++)
		{
			StringEditor::echo(i, param[i]);
		}

		if (paramNum == 1)
		{
			if (param[0].compare(L"closeFile") == 0)
			{
				b = false;
			}
		}
		else if (paramNum == 2)
		{
			if (param[0].compare(L"setWidth") == 0)
			{
				width = stoi(param[1]);
				widthLoaded = true;
			}
			if (param[0].compare(L"setHeight") == 0)
			{
				height = stoi(param[1]);
				heightLoaded = true;
			}
			if (param[0].compare(L"setSpawnX") == 0)
			{
				spawnX = stoi(param[1]);
				spawnXLoaded = true;
			}
			if (param[0].compare(L"setSpawnY") == 0)
			{
				spawnY = stoi(param[1]);
				spawnYLoaded = true;
			}
			if (param[0].compare(L"setSpawnDirection") == 0)
			{
				int d = -1;
				if (param[1].compare(L"UP") == 0) d = 0;
				if (param[1].compare(L"LEFT") == 0) d = 1;
				if (param[1].compare(L"DOWN") == 0) d = 2;
				if (param[1].compare(L"RIGHT") == 0) d = 3;
				p.setDirection(to_Direction(d));
				spawnDirectionLoaded = true;
			}
			if (param[0].compare(L"setNumberOfTeleports") == 0)
			{
				numTeleports = stoi(param[1]);
				teleports = new Teleport[numTeleports];
				teleportsCreated = true;
			}
			if (param[0].compare(L"setNumberOfNPCs") == 0)
			{
				numNPCs = stoi(param[1]);
				npcs = new Player[numNPCs];
				npcsCreated = true;
			}
		}
		else if (paramNum == 5)
		{
			if (param[0].compare(L"setRow") == 0 && mapCreated)
			{
				for (int i = 0; i < width; i++)
				{
					map[i][stoi(param[1])] = Tile(stoi(param[2]), stoi(param[3]), stoi(param[4]));
				}
			}
			if (param[0].compare(L"setCol") == 0 && mapCreated)
			{
				for (int i = 0; i < height; i++)
				{
					map[stoi(param[1])][i] = Tile(stoi(param[2]), stoi(param[3]), stoi(param[4]));
				}
			}
		}
		else if (paramNum == 6)
		{
			if (param[0].compare(L"setBlock") == 0 && mapCreated)
			{
				map[stoi(param[1])][stoi(param[2])] = Tile(stoi(param[3]), stoi(param[4]), stoi(param[5]));
			}
		}
		else if (paramNum == 8)
		{
			if (param[0].compare(L"setTeleport") == 0 && teleportsCreated)
			{
				int d = -1;
				if (param[6].compare(L"UP") == 0) d = 0;
				if (param[6].compare(L"LEFT") == 0) d = 1;
				if (param[6].compare(L"DOWN") == 0) d = 2;
				if (param[6].compare(L"RIGHT") == 0) d = 3;
				teleports[stoi(param[1])] = Teleport(stoi(param[2]), stoi(param[3]), stoi(param[4]), stoi(param[5]), to_Direction(d), stoi(param[7]));
			}
		}
		else if (paramNum == 9)
		{
			if (param[0].compare(L"setTeleport") == 0 && teleportsCreated)
			{
				int d = -1;
				if (param[7].compare(L"UP") == 0) d = 0;
				if (param[7].compare(L"LEFT") == 0) d = 1;
				if (param[7].compare(L"DOWN") == 0) d = 2;
				if (param[7].compare(L"RIGHT") == 0) d = 3;
				teleports[stoi(param[1])] = Teleport(stoi(param[2]), stoi(param[3]), param[4], stoi(param[5]), stoi(param[6]), to_Direction(d), stoi(param[8]));
			}
		}

		if (!mapCreated && heightLoaded && widthLoaded)
		{
			map = new Tile*[width];
			for (int i = 0; i < width; i++)
			{
				map[i] = new Tile[height];
			}
			for (int i = 0; i < width; i++)
			{
				for (int j = 0; j < height; j++)
				{
					map[i][j] = Tile(0, 0, 0);
				}
			}
			mapCreated = true;
		}

		StringEditor::echo(L"==========END OF LOOP ITERATION============");
	}
	filei.close();
	//fileo.close();

	//End of file loading testing code. -Karl

	//Creating Arrays
	if (!widthLoaded) width = 5;
	if (!heightLoaded) height = 5;
	if (!spawnXLoaded) spawnX == width - 1;
	if (!spawnYLoaded) spawnY == height - 1;
	if (!spawnDirectionLoaded) spawnDirection == Direction::RIGHT;
	if (!mapCreated)
	{
		map = new Tile*[width];
		for (int i = 0; i < width; i++)
		{
			map[i] = new Tile[height];
		}
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				map[i][j] = Tile(0, 0, 0);
			}
		}
	}
	
	if (!npcsCreated)
	{
		numNPCs = 0;
		npcs = new Player[numNPCs];
	}

	if (!teleportsCreated)
	{
		numTeleports = 0;
		teleports = new Teleport[numTeleports];
	}

	//LOADING IMAGES

	textureMap = sf::Image();
	textureMap.loadFromFile(PACKS + auth + "/" + pack + "/" + level + "/Spritesheet.png");

	costumeMap = sf::Image();
	costumeMap.loadFromFile(RESOURCES + "Video/Player.png");

	sf::Image dialogBoxImg;
	dialogBoxImg.loadFromFile(RESOURCES + "Video/DialogBox.png");
	dialogBox = sf::Texture();
	dialogBox.loadFromImage(dialogBoxImg);

	textures = new sf::Texture[256];
	for (int i = 0; i < 256; i++) //Creates a list of textures from the spritesheet
	{
		textures[i] = sf::Texture();
		textures[i].loadFromImage(textureMap, sf::IntRect((i % 16) * BLOCK_SIZE, (int)(i / 16) * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE));
	}

	costumes = new sf::Texture[8];
	for (int i = 0; i < 8; i++) //Creates a list of textures from the spritesheet
	{
		costumes[i] = sf::Texture();
		costumes[i].loadFromImage(costumeMap, sf::IntRect((i % 4) * BLOCK_SIZE, (int)(i / 4) * PLAYER_HEIGHT, BLOCK_SIZE, PLAYER_HEIGHT));
	}
}

void Level::update(Controls & c)
{
	if (mode == Mode::REG)
	{
		if (p.isLocked()) //If the player is standing in his tile
		{
			//Check if player is standing on a teleport

			for (int i = 0; i < numTeleports; i++)
			{
				Teleport t = teleports[i];
				if (p.getBlockX() == t.getX() && p.getBlockY() == t.getY())
				{
					if (t.intraLevel())
					{
						//Local Teleport, (inside of the same level)
						p.place(t.getToX(), t.getToY(), t.getDirection());
					}
					else
					{
						//Out of file teleport, old java code below. TODO replace with new C++ listener code
						//l.switchLevels(t.level, t.toX, t.toY, t.getDirection());
						requestLevelChange(t.getName(), t.getToX(), t.getToY(), t.getDirection());
					}
				}
			}

			if (c.isPressed(p.getDirection()) == true && c.getTimePressed(p.getDirection()) > 4 && p.isAllowedToMove()) //If user wants to move
			{
				bool upBlocked = false;
				bool leftBlocked = false;
				bool downBlocked = false;
				bool rightBlocked = false;

				//keep player from leaving the boundaries
				if (p.getBlockY() == 0) { upBlocked = true; }
				if (p.getBlockX() == 0) { leftBlocked = true; }
				if ((p.getBlockY() == (height - 1))) { downBlocked = true; }
				if ((p.getBlockX() == (width - 1))) { rightBlocked = true; }

				//check to make sure npcs aren't in the way
				for (int i = 0; i < numNPCs; i++)
				{
					if (npcs[i].isVisible())
					{
						if (!upBlocked && p.getBlockX() == npcs[i].getBlockX() && (p.getBlockY() - 1) == npcs[i].getBlockY())
						{
							upBlocked = true;
						}
						else if (!leftBlocked && (p.getBlockX() - 1) == npcs[i].getBlockX() && p.getBlockY() == npcs[i].getBlockY())
						{
							leftBlocked = true;
						}
						else if (!downBlocked&& p.getBlockX() == npcs[i].getBlockX() && (p.getBlockY() + 1) == npcs[i].getBlockY())
						{
							downBlocked = true;
						}
						else if (!rightBlocked && (p.getBlockX() + 1) == npcs[i].getBlockX() && p.getBlockY() == npcs[i].getBlockY())
						{
							rightBlocked = true;
						}
					}
				}

				//Final movement validity check
				if (p.getDirection() == Direction::UP)
				{
					if (!upBlocked && Tile::movementValid(map[p.getBlockX()][p.getBlockY()], map[p.getBlockX()][p.getBlockY() - 1]))
					{
						p.setBlockY(p.getBlockY() - 1);
						p.adjustActualY(-4.0f);
					}
				}
				else if (p.getDirection() == Direction::LEFT)
				{
					if (!leftBlocked && Tile::movementValid(map[p.getBlockX()][p.getBlockY()], map[p.getBlockX() - 1][p.getBlockY()]))
					{
						p.setBlockX(p.getBlockX() - 1);
						p.adjustActualX(-4.0f);
					}
				}
				else if (p.getDirection() == Direction::DOWN)
				{
					if (!downBlocked && Tile::movementValid(map[p.getBlockX()][p.getBlockY()], map[p.getBlockX()][p.getBlockY() + 1]))
					{
						p.setBlockY(p.getBlockY() + 1);
						p.adjustActualY(4.0f);
					}
				}
				else if (p.getDirection() == Direction::RIGHT)
				{
					if (!rightBlocked && Tile::movementValid(map[p.getBlockX()][p.getBlockY()], map[p.getBlockX() + 1][p.getBlockY()]))
					{
						p.setBlockX(p.getBlockX() + 1);
						p.adjustActualX(4.0f);
					}
				}
				//The next code is to detect if the player is moving onto a teleport, and if he is, start displaying the going up or down animation if it is needed
				for (int i = 0; i < numTeleports; i++)
				{
					if (teleports[i].getX() == p.getBlockX() && teleports[i].getY() == p.getBlockY())
					{
						p.setZDirection(teleports[i].getZDirection());
						break;
					}
				}
			}
			else if (c.isPressedForFirstTime(Control::ACCEPT)) //Select something, like an npc
			{
				bool directionFacingIsValid = true;

				if (p.getDirection() == Direction::UP && p.getBlockY() == 0) { directionFacingIsValid = false; }
				else if (p.getDirection() == Direction::LEFT && p.getBlockX() == 0) { directionFacingIsValid = false; }
				else if (p.getDirection() == Direction::DOWN && (p.getBlockY() == (height - 1))) { directionFacingIsValid = false; }
				else if (p.getDirection() == Direction::RIGHT && (p.getBlockX() == (width - 1))) { directionFacingIsValid = false; }

				if (directionFacingIsValid)
				{
					for (int i = 0; i < numNPCs; i++)
					{
						if (p.getDirection() == Direction::UP && p.getBlockX() == npcs[i].getBlockX() && p.getBlockY() - 1 == npcs[i].getBlockY())
						{
							dialogNPCNum = i;
							mode = Mode::DIALOG;
						}
						else if (p.getDirection() == Direction::LEFT && p.getBlockX() - 1 == npcs[i].getBlockX() && p.getBlockY() == npcs[i].getBlockY())
						{
							dialogNPCNum = i;
							mode = Mode::DIALOG;
						}
						else if (p.getDirection() == Direction::DOWN && p.getBlockX() == npcs[i].getBlockX() && p.getBlockY() + 1 == npcs[i].getBlockY())
						{
							dialogNPCNum = i;
							mode = Mode::DIALOG;
						}
						else if (p.getDirection() == Direction::RIGHT && p.getBlockX() + 1 == npcs[i].getBlockX() && p.getBlockY() == npcs[i].getBlockY())
						{
							dialogNPCNum = i;
							mode = Mode::DIALOG;
						}
					}
				}
			}
			else //Change the player's direction
			{
				if (c.isPressed(Control::C_UP) && !c.isPressed(Control::C_LEFT) && !c.isPressed(Control::C_DOWN) && !c.isPressed(Control::C_RIGHT))
					p.setDirection(Direction::UP);
				else if (!c.isPressed(Control::C_UP) && c.isPressed(Control::C_LEFT) && !c.isPressed(Control::C_DOWN) && !c.isPressed(Control::C_RIGHT))
					p.setDirection(Direction::LEFT);
				else if (!c.isPressed(Control::C_UP) && !c.isPressed(Control::C_LEFT) && c.isPressed(Control::C_DOWN) && !c.isPressed(Control::C_RIGHT))
					p.setDirection(Direction::DOWN);
				else if (!c.isPressed(Control::C_UP) && !c.isPressed(Control::C_LEFT) && !c.isPressed(Control::C_DOWN) && c.isPressed(Control::C_RIGHT))
					p.setDirection(Direction::RIGHT);
			}
		}
		else //If the player is not standing in his tile, e.g. he is walking
		{
			if (p.getActualY() - 4.0f>(float)p.getBlockY() * BLOCK_SIZE) p.adjustActualY(-4.0f);
			else if ((int)p.getActualY() > p.getBlockY() * BLOCK_SIZE) p.setActualY((float)p.getBlockY() * BLOCK_SIZE);

			if (p.getActualX() - 4.0f>(float)p.getBlockX() * BLOCK_SIZE) p.adjustActualX(-4.0f);
			else if ((int)p.getActualX()>p.getBlockX() * BLOCK_SIZE) p.setActualX((float)p.getBlockX() * BLOCK_SIZE);

			if (p.getActualY() + 4.0f<(float)p.getBlockY() * BLOCK_SIZE) p.adjustActualY(4.0f);
			else if ((int)p.getActualY()<p.getBlockY() * BLOCK_SIZE) p.setActualY((float)p.getBlockY() * BLOCK_SIZE);

			if (p.getActualX() + 4.0f < (float)p.getBlockX() * BLOCK_SIZE) p.adjustActualX(4.0f);
			else if ((int)p.getActualX()<p.getBlockX() * BLOCK_SIZE) p.setActualX((float)p.getBlockX() * BLOCK_SIZE);
		}
	}
	else if (mode == Mode::DIALOG)
	{
		if (c.isPressedForFirstTime(Control::ACCEPT))
		{
			if (npcs[dialogNPCNum].getWantsToBattle()) 
			{
				requestBattleScreen();
			}
			else
			{
				dialogNPCNum = -1;
				mode = Mode::REG;
			}
		}
	}
}

void Level::render(sf::RenderWindow & window, KText & font)
{
	//Set the view
	sf::View view;
	view.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	view.setCenter(sf::Vector2f(p.getActualX() + 32, p.getActualY() + 32));
	window.setView(view);

	//Draw blocks
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			sf::Sprite s(textures[map[i][j].getImgNum()]);
			s.setPosition(sf::Vector2f((float)i * BLOCK_SIZE, (float)j * BLOCK_SIZE));
			window.draw(s);
		}
	}
	//Draw character if above NPC
	if (!ifPlayerIsUnderNPC())
	{
		drawPlayer(window);
	}

	//DRAW NPCS
	for (int i = 0; i < numNPCs; i++)
	{
		if (npcs[i].isVisible())
		{
			sf::Sprite s(costumes[npcs[i].getDirection() + (npcs[i].getGender() * 4)]);
			s.setPosition(sf::Vector2f(npcs[i].getActualX(), npcs[i].getActualY() - (PLAYER_HEIGHT - BLOCK_SIZE)));
			window.draw(s);
		}
	}

	//Draw character if below npc
	if (ifPlayerIsUnderNPC())
	{
		drawPlayer(window);
	}

	if (mode == Mode::DIALOG)
	{
		drawDialog(window, font);
	}
}

void Level::drawDialog(sf::RenderWindow & window, KText & font)
{
	/*
	  THIS METHOD IS GOING TO EXPORTED TO IT'S OWN CLASS SOON, DON'T FRET
	  THIS METHOD ALSO IS GOING TO BE VERY BIG AND COMPLICATED, THEREFORE I (KARL) WILL WORK ON IT BECAUSE IT REQUIRES
	DEPTH OF KNOWLEDGE IN PROGRAMMING FOR NON-ASCII SYMBOLS AND OTHER FANCY TECHNIQUES I AM ADDING. 
	-KARL PIEPHO
	*/


	//Set the view
	sf::View view;
	view.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	view.setCenter(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	window.setView(view);

	sf::Sprite s(dialogBox);
	s.setPosition(0, DIALOG_BOX_LOW);
	window.draw(s);

	font.levelDialog(window, npcs[dialogNPCNum].getDialog());
}

void Level::requestLevelChange(wstring name, int x, int y, Direction d)
{
	Level::toLevelName = name;
	Level::toLevelX = x;
	Level::toLevelY = y;
	Level::toLevelDirection = d;
	Level::levelRequestsChange = true;
}
void Level::requestBattleScreen()
{
	Level::levelRequestsBattle = true;
}

bool Level::ifPlayerIsUnderNPC()
{
	if (p.getBlockY() == 0)
	{
		return false;
	}
	for (int i = 0; i < numNPCs; i++)
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

void Level::drawPlayer(sf::RenderWindow & window)
{
	sf::Sprite s(costumes[p.getDirection() + (p.getGender() * 4)]);
	//The rendering class actually handles the player appearing to move up and down the steps rather than editing the actual coordinates and making some really strange code
	if (p.getZDirection() == 0)
	{
		s.setPosition(sf::Vector2f(p.getActualX(), p.getActualY() - (PLAYER_HEIGHT - BLOCK_SIZE)));
	}
	else if (p.getZDirection() == 1 && p.getDirection() == 1) //if player is going up the stairs to the left
	{
		s.setPosition(sf::Vector2f(p.getActualX(), p.getActualY() - (.25f * (64 - (p.getActualX() - (p.getBlockX() * 64)))) - (PLAYER_HEIGHT - BLOCK_SIZE)));
	}
	else if (p.getZDirection() == 1 && p.getDirection() == 3) //if player is going up the stairs to the right
	{
		s.setPosition(sf::Vector2f(p.getActualX(), p.getActualY() - (.5f * (64 - ((p.getBlockX() * 64) - p.getActualX()))) - (PLAYER_HEIGHT - BLOCK_SIZE)));
	}
	else if (p.getZDirection() == -1 && p.getDirection() == 1) //if player is going down the stairs to the left
	{
		s.setPosition(sf::Vector2f(p.getActualX(), p.getActualY() + (.25f * (64 - (p.getActualX() - (p.getBlockX() * 64)))) - (PLAYER_HEIGHT - BLOCK_SIZE)));
	}
	else if (p.getZDirection() == -1 && p.getDirection() == 3) //if player is going down the stairs to the right
	{
		s.setPosition(sf::Vector2f(p.getActualX(), p.getActualY() - (.5f * (64 - ((p.getBlockX() * 64) - p.getActualX()))) - (PLAYER_HEIGHT - BLOCK_SIZE)));
	}
	window.draw(s);
}