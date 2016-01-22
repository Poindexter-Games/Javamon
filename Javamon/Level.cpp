#include "Level.h"

using namespace std;

Level::Level()
{
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
	textureMap.loadFromFile("C:/Users/Karl/Source/Repos/Javamon/Javamon/Resources/Packs/" + auth + "/" + pack + "/" + name + "/Spritesheet.png");

	costumeMap = sf::Image();
	costumeMap.loadFromFile("C:/Users/Karl/Source/Repos/Javamon/Javamon/Resources/Video/Player.png");

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

	//TODO Implement loading from resource/pack/level.txt
	name = level;

	//This is some testing code, it doesn't work correctly, so it will be removed soon 

	Level::auth = auth;
	Level::pack = pack;
	Level::name = level;

	ifstream file;
	file.open("C:/Users/Karl/Source/Repos/Javamon/Javamon/Resources/Packs/" + auth + "/" + pack + "/" + level + "/Level.txt");
	for (string line; getline(file, line); )
	{
		//...for each line in input...
		cout << "l: " << line << endl;
		if (line.substr(0, 8).compare("setName,") == 0)
		{
			dispName = line.substr(8, line.length() - 8);
			cout << dispName << endl;
		}
	}
	file.close();

	//End of file loading testing code. -Karl
}

void Level::newLevel(int n, int x, int y, int d)
{
	levelRequestsChange = false;

	Level::auth = "Poindexter";
	Level::pack = "Test";

	Level::p = Player();

	if (n == 0) //Red's room in pkmn fr
	{
		Level::name = "Level_FRLG";
		width = 11;
		height = 9;
		numTeleports = 2;
		if (x == -1 && y == -1 && d == -1)
		{
			//This means that this level is the first level being initialized (user just started the game)
			p.setBlockX(5);
			p.setBlockY(7);
			p.setActualX(5 * BLOCK_SIZE);
			p.setActualY(7 * BLOCK_SIZE);
			p.setDirection(2);
		}
		else
		{
			//This means that the player has moved from a different level to this one and the other level has already designated its toX and toY co-ordinates
			p.setBlockX(x);
			p.setBlockY(y);
			p.setActualX(x * BLOCK_SIZE);
			p.setActualY(y * BLOCK_SIZE);
			//This offsets the player and allows them to walk into the level, or off of the stairs
			if (d == 0) { p.setDirection(0); p.setActualY((y + .5) * BLOCK_SIZE); }
			if (d == 1) { p.setDirection(1); p.setActualX((x + .5) * BLOCK_SIZE); }
			if (d == 2) { p.setDirection(2); p.setActualY((y - .5) * BLOCK_SIZE); }
			if (d == 3) { p.setDirection(3); p.setActualX((x - .5) * BLOCK_SIZE); }
		}
	}
	else if (n == 1) //Red's living room in pkmn fr
	{
		Level::name = "Level_FRLG";
		width = 12;
		height = 9;
		numTeleports = 1;
		if (x == -1 && y == -1 && d == -1)
		{
			p.setBlockX(1);
			p.setBlockY(1);
			p.setActualX(1 * BLOCK_SIZE);
			p.setActualY(1 * BLOCK_SIZE);
			p.setDirection(2);
		}
		else
		{
			//This means that the player has moved from a different level to this one and the other level has already designated its toX and toY co-ordinates
			p.setBlockX(x);
			p.setBlockY(y);
			p.setActualX(x * BLOCK_SIZE);
			p.setActualY(y * BLOCK_SIZE);
			//This offsets the player and allows them to walk into the level, or off of the stairs
			if (d == 0) { p.setDirection(0); p.setActualY((y + .5) * BLOCK_SIZE); }
			if (d == 1) { p.setDirection(1); p.setActualX((x + .5) * BLOCK_SIZE); }
			if (d == 2) { p.setDirection(2); p.setActualY((y - .5) * BLOCK_SIZE); }
			if (d == 3) { p.setDirection(3); p.setActualX((x - .5) * BLOCK_SIZE); }
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

	teleports = new Teleport[numTeleports];

	//MAP EDITS HERE
	if (n == 0)
	{
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
		teleports[0] = Teleport(10, 8, 0, 8, 2, 0);
		teleports[1] = Teleport(9, 2, "Level_FRLG_1", 9, 2, 1, -1);
	}
	else if (n == 1)
	{
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
		teleports[0] = Teleport(10, 2, "Level_FRLG_0",  10, 2, 3, 1);
	}

	textureMap = sf::Image();
	textureMap.loadFromFile("C:/Users/Karl/Source/Repos/Javamon/Javamon/Resources/Packs/" + auth + "/" + pack + "/" + name + "/Spritesheet.png");

	costumeMap = sf::Image();
	costumeMap.loadFromFile("C:/Users/Karl/Source/Repos/Javamon/Javamon/Resources/Video/Player.png");

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
}

void Level::update(bool* digitalControls)
{
	// 0   w
	//123 asd
	if(p.isLocked()) //If the player is standing in his tile
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
					p.setActualX(t.getToX() * BLOCK_SIZE);
					p.setActualY(t.getToY() * BLOCK_SIZE);
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

		//End teleport check
		//Begin check if player wants to move


		if (digitalControls[p.getDirection()] == true && p.isAllowedToMove()) //If user is pressing the direction that the character is facing
		{
			if (p.getDirection() == 0) //Is player's direction up
			{
				if (p.getBlockY ()!= 0 && Tile::movementValid(map[p.getBlockX()][p.getBlockY()], map[p.getBlockX()][p.getBlockY()-1]))
				{
					p.setBlockY(p.getBlockY() - 1);
					p.adjustActualY(-3.2f);
				}
			}
			else if (p.getDirection() == 1) //Left
			{
				if (p.getBlockX() != 0 && Tile::movementValid(map[p.getBlockX()][p.getBlockY()], map[p.getBlockX()-1][p.getBlockY()]))
				{
					p.setBlockX(p.getBlockX() - 1);
					p.adjustActualX(-3.2f);
				}
			}
			else if (p.getDirection() == 2) //Down
			{
				if (p.getBlockY() != (height - 1) && Tile::movementValid(map[p.getBlockX()][p.getBlockY()], map[p.getBlockX()][p.getBlockY()+1]))
				{
					p.setBlockY(p.getBlockY() + 1);
					p.adjustActualY(3.2f);
				}
			}
			else if (p.getDirection() == 3) //Right
			{
				if (p.getBlockX() != (width - 1) && Tile::movementValid(map[p.getBlockX()][p.getBlockY()], map[p.getBlockX()+1][p.getBlockY()]))
				{
					p.setBlockX(p.getBlockX() + 1);
					p.adjustActualX(3.2f);
				}
			}
			cout << p.getBlockX() << " " << p.getBlockY() << endl;
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
		else
		{
			if (digitalControls[0] && !digitalControls[1] && !digitalControls[2] && !digitalControls[3])
				p.setDirection(0);
			else if (!digitalControls[0] && digitalControls[1] && !digitalControls[2] && !digitalControls[3])
				p.setDirection(1);
			else if (!digitalControls[0] && !digitalControls[1] && digitalControls[2] && !digitalControls[3])
				p.setDirection(2);
			else if (!digitalControls[0] && !digitalControls[1] && !digitalControls[2] && digitalControls[3])
				p.setDirection(3);
		}
	}
	else //If the player is not standing in his tile, e.g. he is walking
	{
		if (p.getActualY() - 3.2f>(float)p.getBlockY() * BLOCK_SIZE) p.adjustActualY(-3.2f);
		else if ((int)p.getActualY() > p.getBlockY() * BLOCK_SIZE) p.setActualY((float)p.getBlockY() * BLOCK_SIZE);

		if (p.getActualX() - 3.2f>(float)p.getBlockX() * BLOCK_SIZE) p.adjustActualX(-3.2f);
		else if ((int)p.getActualX()>p.getBlockX() * BLOCK_SIZE) p.setActualX((float)p.getBlockX() * BLOCK_SIZE);

		if (p.getActualY() + 3.2f<(float)p.getBlockY() * BLOCK_SIZE) p.adjustActualY(3.2f);
		else if ((int)p.getActualY()<p.getBlockY() * BLOCK_SIZE) p.setActualY((float)p.getBlockY() * BLOCK_SIZE);

		if (p.getActualX() + 3.2f < (float)p.getBlockX() * BLOCK_SIZE) p.adjustActualX(3.2f);
		else if((int)p.getActualX()<p.getBlockX() * BLOCK_SIZE) p.setActualX((float)p.getBlockX() * BLOCK_SIZE);
	}

	/*
	This is outrageous! Another section of random Java code laying around!
	if(p.x==p.targetX && p.y == p.targetY)
		{
			for(int i = 0; i < teleports.size(); i++)
			{
				Teleport t = teleports.get(i);
				if(p.x == t.x * 60 && p.y == t.y * 60)
				{
					if(t.level.equals("local"))
					{
						//Local Teleport
						p.x = t.toX * 60;
						p.y = t.toY * 60;
						p.targetX = t.toX * 60;
						p.targetY = t.toY * 60;
					}
					else
					{
						//Out of file teleport
						l.switchLevels(t.level, t.toX, t.toY, t.getDirection());
					}
				}
			}
			
			if(p.d.equals(d)) //<C++> If the player direction equals the direction the user wants to go in </C++>
			{
				boolean doesMove = false;
				float oldX = -1, oldY = -1;	
				
				//Check for altitude and move
				try
				{
					if((d==Direction.NORTH && (north.altitude<=current.altitude || north.altitude==current.altitude+1)) && time > 80)
					{
						doesMove = true;
						p.targetY-=60;
						oldX = p.x; oldY = p.y;
					}
					else if((d==Direction.SOUTH && (south.altitude<=current.altitude || south.altitude==current.altitude+1)) && time > 80)
					{
						doesMove = true;
						p.targetY+=60;
						oldX = p.x; oldY = p.y;
					}
					else if((d==Direction.WEST && (west.altitude<=current.altitude || west.altitude==current.altitude+1)) && time > 80)
					{
						doesMove = true;
						p.targetX-=60;
						oldX = p.x; oldY = p.y;
					}
					else if((d==Direction.EAST && (east.altitude<=current.altitude || east.altitude==current.altitude+1)) && time > 80)
					{
						doesMove = true;
						p.targetX+=60;
						oldX = p.x; oldY = p.y;
					}
				}catch(NullPointerException e){}
				
				//Now check for people
				try
				{
					for(int i = 0; i < npcs.size(); i++)
					{
						NPC temp = npcs.get(i);
						if(temp.getX()==p.targetX / 60 && temp.getY()==p.targetY / 60)
						{
							if(doesMove && !(oldX == -1 && oldY == -1))
							{
								p.targetX = oldX;
								p.targetY = oldY;
							}
						}
					}
				}catch(NullPointerException e){}
				
				if(p.targetX>(width-1)*60)p.targetX=(width-1)*60;
				if(p.targetY>(height-1)*60)p.targetY=(height-1)*60;
			}
			else if(!d.equals(Direction.NONE))
			{
				p.d = d;
			}
		}
		else  //<C++> If the player is in-between blocks </C++>
		{
			if(p.x+p.speed<p.targetX) p.x+=p.speed;
			else if(p.x<p.targetX) p.x = p.targetX;
			
			if(p.x-p.speed>p.targetX) p.x-=p.speed;
			else if(p.x>p.targetX) p.x = p.targetX;
			
			
			if(p.y+p.speed<p.targetY) p.y+=p.speed;
			else if(p.y<p.targetY) p.y = p.targetY;
			
			if(p.y-p.speed>p.targetY) p.y-=p.speed;
			else if(p.y>p.targetY) p.y = p.targetY;
		}
	*/
}

void Level::render(sf::RenderWindow & window)
{
	//Set the view
	sf::View view;
	view.setSize(sf::Vector2f(1280, 720));
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
	//Draw character
	sf::Sprite s(costumes[p.getDirection() + (p.getGender() * 4)]);
	//The rendering class actually handles the player appearing to move up and down the steps rather than editing the actual coordinates and making some really strange code
	if(p.getZDirection() == 0)
	{
		s.setPosition(sf::Vector2f(p.getActualX(), p.getActualY()));
	}
	else if (p.getZDirection() == 1 && p.getDirection() == 1) //if player is going up the stairs to the left
	{
		s.setPosition(sf::Vector2f(p.getActualX(), p.getActualY() - (.25f * (64 - (p.getActualX() - (p.getBlockX() * 64)))) + 0));
	}
	else if (p.getZDirection() == 1 && p.getDirection() == 3) //if player is going up the stairs to the right
	{
		s.setPosition(sf::Vector2f(p.getActualX(), p.getActualY() - (.5f * (64 - ((p.getBlockX() * 64) - p.getActualX()))) + 0));
	}
	else if (p.getZDirection() == -1 && p.getDirection() == 1) //if player is going down the stairs to the left
	{
		s.setPosition(sf::Vector2f(p.getActualX(), p.getActualY() + (.25f * (64 - (p.getActualX() - (p.getBlockX() * 64)))) + 0));
	}
	else if (p.getZDirection() == -1 && p.getDirection() == 3) //if player is going down the stairs to the right
	{
		s.setPosition(sf::Vector2f(p.getActualX(), p.getActualY() - (.5f * (64 - ((p.getBlockX() * 64) - p.getActualX()))) + 0));
	}
	window.draw(s);
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