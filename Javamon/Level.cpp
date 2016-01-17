#include "Level.h"

using namespace std;

Level::Level(Events& e)
{
	Level::eventListener = e;

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
		textures[i].loadFromImage(textureMap, sf::IntRect((i % 16) * 64, (int)(i / 16) * 64, 64, 64));
	}

	costumes = new sf::Texture[8];
	for (int i = 0; i < 8; i++) //Creates a list of textures from the spritesheet
	{
		costumes[i] = sf::Texture();
		costumes[i].loadFromImage(costumeMap, sf::IntRect((i % 4) * 64, (int)(i / 4) * 64, 64, 64));
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

Level::Level(string somerandomstringnameinordertomakethisnotseemlikeadefaultconstructor)
{
	Level::pack = "Karl"; //I don't want to bother with spelling poindexter
	Level::name = "Test";
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
	map[1][1] = Tile(1, 0, 0);

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
		textures[i].loadFromImage(textureMap, sf::IntRect((i % 16) * 64, (int)(i / 16) * 64, 64, 64));
	}

	costumes = new sf::Texture[8];
	for (int i = 0; i < 8; i++) //Creates a list of textures from the spritesheet
	{
		costumes[i] = sf::Texture();
		costumes[i].loadFromImage(costumeMap, sf::IntRect((i % 4) * 64, (int)(i / 4) * 64, 64, 64));
	}
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

void Level::update(bool* digitalControls)
{
	// 0   w
	//123 asd
	if(p.isLocked()) //If the player is standing in his tile
	{
		if (digitalControls[p.getDirection()] == true) //If player is facing the direction he wants to go
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
			/*switch (p.getDirection())
			{
			case 0:
				p.setBlockY(p.getBlockY()-1);
				p.adjustActualY(-3.2f);
				break;
			case 1:
				p.setBlockX(p.getBlockX()-1);
				p.adjustActualX(-3.2f);
				break;
			case 2:
				p.setBlockY(p.getBlockY()+1);
				p.adjustActualY(3.2f);
				break;
			case 3:
				p.setBlockX(p.getBlockX()+1);
				p.adjustActualX(3.2f);
				break;
			}*/
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
		if (p.getActualY() - 3.2f>(float)p.getBlockY() * 64) p.adjustActualY(-3.2f);
		else if ((int)p.getActualY() > p.getBlockY() * 64) p.setActualY((float)p.getBlockY() * 64);

		if (p.getActualX() - 3.2f>(float)p.getBlockX() * 64) p.adjustActualX(-3.2f);
		else if ((int)p.getActualX()>p.getBlockX() * 64) p.setActualX((float)p.getBlockX() * 64);

		if (p.getActualY() + 3.2f<(float)p.getBlockY() * 64) p.adjustActualY(3.2f);
		else if ((int)p.getActualY()<p.getBlockY() * 64) p.setActualY((float)p.getBlockY() * 64);

		if (p.getActualX() + 3.2f < (float)p.getBlockX() * 64) p.adjustActualX(3.2f);
		else if((int)p.getActualX()<p.getBlockX() * 64) p.setActualX((float)p.getBlockX() * 64);
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
	sf::View view;
	view.setSize(sf::Vector2f(1280, 720));
	view.setCenter(sf::Vector2f(p.getActualX() + 32, p.getActualY() + 32));
	window.setView(view);

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			sf::Sprite s(textures[map[i][j].getImgNum()]);
			s.setPosition(sf::Vector2f((float)i * 64, (float)j * 64));
			window.draw(s);
		}
	}
	sf::Sprite s(costumes[p.getDirection() + (p.getGender() * 4)]);
	s.setPosition(sf::Vector2f(p.getActualX(), p.getActualY()));
	window.draw(s);
}

void Level::setName(string name)
{
	Level::name = name;
}