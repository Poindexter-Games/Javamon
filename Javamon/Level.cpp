#include "Level.h"

using namespace std;

Level::Level()
{
	sf::FileInputStream fs;

	Level::auth = "Poindexter";
	Level::pack = "Test";
	Level::name = "TestLevel";
	width = 8;
	height = 8;

	Player p;

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
	//TEMPORARY EDIT MAP HERE
	map[2][1] = Tile(1, 2, 0);
	map[3][1] = Tile(2, 1, 0);

	textureMap = sf::Image();
	textureMap.loadFromFile(RESOURCES + "Packs/" + auth + "/" + pack + "/" + name + "/Spritesheet.png");

	costumeMap = sf::Image();
	costumeMap.loadFromFile(RESOURCES + "Video/Player.png");

	/*
	//Listening to Leeroy jenkins remix 10 hours
	//Time straight = 54:07 (54 minutes 07 seconds) I couldn't make it to an hour...

	for(int i = 0; i < blocks.size(); i++)
	{
	g.drawImage(images.get(blocks.get(i).imageId()), ((i%width)*60)+xOffset, (Math.roundDown(i/width)*60)+yOffset, null);
	}
	*/

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
		costumes[i].loadFromImage(costumeMap, sf::IntRect((i % 4) * BLOCK_SIZE, (int)(i / 4) * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE));
	}

	//==

	/*
	void loadLevel
	{
		fstream file;
		file.open("");
		file.close();
	}
	*/	
}

Level::Level(int n, int x, int y, int d)
{
	newLevel(n, x, y, d);
}

Level::Level(string auth, string pack, string level)
{
	//This is some testing code, it doesn't work correctly, so it will be removed soon 

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
	bool numNPCsLoaded = false;
	bool numTeleportsLoaded = false;

	Level::p = Player();

	wifstream file;
	file.open(RESOURCES + "Packs/" + auth + "/" + pack + "/" + level + "/Level.txt");

	wstring line;			//This is the file of the line
	getline(file, line);	//This is to ignore the first line of the file, which contains the BOM character
	wstring param;			//This is the wstring to hold what command/parameter is to be used

	for (bool b = true; b;)
	{
		getline(file, line);													//Get line
		param = StringEditor::popOffParameter(line);							//Get command

		StringEditor::echo(L"PARAM: " + param);

		if (param.compare(L"setName"))
		{
			StringEditor::echo(L"Parameter was set name");
		}
		if (param.compare(L"setWidth"))
		{
			wstring width = StringEditor::popOffParameter(param);
			//Level::width = stoi(width);
		}
		if (param.compare(L"setHeight"))
		{
			wstring height = StringEditor::popOffParameter(param);
			//Level::height = stoi(height);
		}

		if (line.compare(L"endFile"))
		{
			b = false;
		}

		StringEditor::echo(L"==========END OF LOOP ITERATION============");		//Tell command prompt that the user has read a line
	}
	file.close();

	wcout << L"Width: " << to_wstring(width) << L" Height: " << to_wstring(height) << endl;

	//End of file loading testing code. -Karl

	//Creating Arrays
	if (!widthLoaded) width = 5;
	if (!heightLoaded) height = 5;


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

	npcs = new Player[numNPCs];
	for (int i = 0; i < numNPCs; i++)
	{
		npcs[i] = Player();
	}

	teleports = new Teleport[numTeleports];

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

void Level::newLevel(int n, int x, int y, int d)
{
	mode = Mode::REG;

	levelRequestsChange = false;
	levelRequestsBattle = false;
	dialogNPCNum = -1;

	Level::auth = "Poindexter";
	Level::pack = "Test";

	Level::p = Player();

	if (n == 0) //Red's room in pkmn fr
	{
		Level::name = "Level_FRLG";
		width = 11;
		height = 9;
		numTeleports = 2;
		numNPCs = 0;
		if (x == -1 && y == -1 && d == -1)
		{
			//This means that this level is the first level being initialized (user just started the game)
			p.setBlockX(5);
			p.setBlockY(7);
			p.setActualX(5 * BLOCK_SIZE);
			p.setActualY(7 * BLOCK_SIZE);
			p.setDirection(Direction::DOWN);
		}
		else
		{
			//This means that the player has moved from a different level to this one and the other level has already designated its toX and toY co-ordinates
			p.place(x, y);
			//This offsets the player and allows them to walk into the level, or off of the stairs
			if (d == 0) { p.setDirection(Direction::UP   ); p.setActualY((y + .5f) * BLOCK_SIZE); }
			if (d == 1) { p.setDirection(Direction::LEFT ); p.setActualX((x + .5f) * BLOCK_SIZE); }
			if (d == 2) { p.setDirection(Direction::DOWN ); p.setActualY((y - .5f) * BLOCK_SIZE); }
			if (d == 3) { p.setDirection(Direction::RIGHT); p.setActualX((x - .5f) * BLOCK_SIZE); }
		}
	}
	else if (n == 1) //Red's living room in pkmn fr
	{
		Level::name = "Level_FRLG";
		width = 12;
		height = 9;
		numTeleports = 1;
		numNPCs = 2;
		if (x == -1 && y == -1 && d == -1)
		{
			p.setBlockX(1);
			p.setBlockY(1);
			p.setActualX(1 * BLOCK_SIZE);
			p.setActualY(1 * BLOCK_SIZE);
			p.setDirection(Direction::DOWN);
		}
		else
		{
			//This means that the player has moved from a different level to this one and the other level has already designated its toX and toY co-ordinates
			p.place(x, y);
			//This offsets the player and allows them to walk into the level, or off of the stairs
			if (d == 0) { p.setDirection(Direction::UP   ); p.setActualY((y + .5f) * BLOCK_SIZE); }
			if (d == 1) { p.setDirection(Direction::LEFT ); p.setActualX((x + .5f) * BLOCK_SIZE); }
			if (d == 2) { p.setDirection(Direction::DOWN ); p.setActualY((y - .5f) * BLOCK_SIZE); }
			if (d == 3) { p.setDirection(Direction::RIGHT); p.setActualX((x - .5f) * BLOCK_SIZE); }
		}
	}

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
	
	npcs = new Player[numNPCs];
	for (int i = 0; i < numNPCs; i++)
	{
		npcs[i] = Player();
	}

	teleports = new Teleport[numTeleports];

	//MAP EDITS HERE
	if (n == 0)
	{
		dispName = L"FRLG_0";
		//Map 0 block edits
		for (int i = 0; i < width; i++)
		{
			map[i][0] = Tile(1, 2, 0);
		}
		for (int i = 0; i < width; i++)
		{
			map[i][1] = Tile(17, 2, 0);
		}
		for (int i = 0; i < width; i++)
		{
			map[i][2] = Tile(16, 0, 0);
		}
		map[10][8] = Tile(2, 0, 0);
		map[0][8] = Tile(18, 0, 0);

		map[8][1] = Tile(48, 2, 0);
		map[8][2] = Tile(64, 2, 0);
		map[9][2] = Tile(65, 0, 0); //This is the block where the teleport is located
		map[8][3] = Tile(80, 2, 0);
		map[9][3] = Tile(81, 2, 0);
		//Map 0 teleport edits
		teleports[0] = Teleport(10, 8, 0, 8, Direction::DOWN, 0);
		teleports[1] = Teleport(9, 2, "Level_FRLG_1", 9, 2, Direction::LEFT, -1);
	}
	else if (n == 1)
	{
		dispName = L"FRLG_1";
		//Map 1 block edits
		for (int i = 0; i < width; i++)
		{
			map[i][0] = Tile(1, 2, 0);
		}
		for (int i = 0; i < width; i++)
		{
			map[i][1] = Tile(17, 2, 0);
		}
		for (int i = 0; i < width; i++)
		{
			map[i][2] = Tile(16, 0, 0);
		}
		map[10][1] = Tile(50, 2, 0);
		map[11][1] = Tile(51, 2, 0);
		map[10][2] = Tile(66, 0, 0); //This is the block where the teleport is located
		map[11][2] = Tile(67, 2, 0);
		map[10][3] = Tile(82, 2, 0);
		map[11][3] = Tile(83, 2, 0);
		//Map 1 teleport edits
		teleports[0] = Teleport(10, 2, "Level_FRLG_0",  10, 2, Direction::RIGHT, 1);
		//Map 1 npc edits
		npcs[0].setGender(Gender::FEMALE);
		npcs[0].place(7, 4);
		npcs[0].setDirection(Direction::LEFT);

		//npcs[0].setDialog(L"トバイキローはだれ？");
		npcs[0].setDialog(L"You down with Donald?");

		npcs[1].place(4, 4);
		npcs[1].setDirection(Direction::RIGHT);
		npcs[1].setDialog(L"You're gonna feel the\nburn of Bernie Sanders.");
		npcs[1].setWantsToBattle(true);
	}

	//LOADING IMAGES

	textureMap = sf::Image();
	textureMap.loadFromFile(RESOURCES + "Packs/" + auth + "/" + pack + "/" + name + "/Spritesheet.png");

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
						p.setBlockX(t.getToX());
						p.setBlockY(t.getToY());
						p.setActualX((float)(t.getToX() * BLOCK_SIZE));
						p.setActualY((float)(t.getToY() * BLOCK_SIZE));
						p.setDirection(t.getDirection());
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
				else if (p.getBlockX() == 0) { leftBlocked = true; }
				else if ((p.getBlockY() == (height - 1))) { downBlocked = true; }
				else if ((p.getBlockX() == (width - 1))) { rightBlocked = true; }

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

void Level::setName(string name)
{
	Level::name = name;
}

void Level::requestLevelChange(string name, int x, int y, int d)
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