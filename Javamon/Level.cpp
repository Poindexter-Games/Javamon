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
	width = 0;
	height = 0;

	transparentOverhangTiles = vector<Tile>();
	opaqueOverhangTiles = vector<Tile>();

	/*
	TO DO - TODO
	Put the request level change flag in the player class
	and have the SinglePlayer.cpp access the level's player class
	*/
	requestsLevelChange = false;
	Level::auth = auth;
	Level::pack = pack;
	Level::name = name;

	/*
	Create a default name for the file if none are loaded
	*/
	Word codeName;
	codeName.langCode = sf::String(L"code_CODE");
	codeName.str = name;
	names.push_back(codeName);

	KFile file(PACKS + auth + L"/" + pack + L"/" + name + L"/Level.txt");
	wstring w;

	/*
	True if reading through multiline comments
	*/
	bool comment = false;

	/*
	Start reading the file
	*/
	for (bool b = true; b; )
	{
		file.readLine(w);

		if (w.length() >= 2 && StringEditor::equals(StringEditor::substring(w, w.length() - 2, w.length()), L"*/"))
		{
			//If line ends with */ then end comment mode
			comment = false;
			continue;
		}
		else if (comment || StringEditor::startsWith(w, L"//"))
		{
			//Skip the line if it is a single line comment or in comment mode
			continue;
		}
		
		else if(StringEditor::startsWith(w, L"\*"))
		{
			//If starting a multiline comment, ignore everything until the */
			comment = true;
			continue;
		}

		else if (StringEditor::startsWith(w, L"setSize"))
		{
			int openParenthesis = StringEditor::findCharacter(w, L'(', 1);
			int comma = StringEditor::findCharacter(w, L',', 1);
			int closeParenthesis = StringEditor::findCharacter(w, L')', 1);

			try
			{
				wstring sWidth = StringEditor::substring(w, openParenthesis + 1, comma);
				wstring sHeight = StringEditor::substring(w, comma + 1, closeParenthesis);

				width = stoi(sWidth);
				height = stoi(sHeight);

				StringEditor::echo(L"sWidth:\t" + to_wstring(width) + L"\tsHeight:\t" + to_wstring(height));

				map = new Tile*[width];
				for (int i = 0; i < width; i++)
				{
					map[i] = new Tile[height];
				}

				for (int i = 0; i < width; i++)
				{
					for (int j = 0; j < height; j++)
					{
						map[i][j] = Tile();
					}
				}
			}
			catch (exception e)
			{
				StringEditor::echo(sf::String(e.what()));
			}
		}

		else if (StringEditor::startsWith(w, L"setSpawn"))
		{
			int openParenthesis = StringEditor::getFirstAppearanceIn(w, L'(');
			int comma_1 = StringEditor::getFirstAppearanceIn(w, L',');
			int comma_2 = StringEditor::findCharacter(w, L',', 2);
			int closeParenthesis = StringEditor::getFirstAppearanceIn(w, L')');

			try
			{
				wstring sX = StringEditor::substring(w, openParenthesis + 1, comma_1);
				wstring sY = StringEditor::substring(w, comma_1 + 1, comma_2);
				wstring sDir = StringEditor::substring(w, comma_2 + 1, closeParenthesis);

				if (StringEditor::equals(sDir, L"UP"))
				{
					spawnDirection = Direction::UP;
				}
				else if (StringEditor::equals(sDir, L"LEFT"))
				{
					spawnDirection = Direction::LEFT;
				}
				else if (StringEditor::equals(sDir, L"DOWN"))
				{
					spawnDirection = Direction::DOWN;
				}
				else if (StringEditor::equals(sDir, L"RIGHT"))
				{
					spawnDirection = Direction::RIGHT;
				}
				else
				{
					spawnDirection = to_Direction(stoi(sDir));
				}

				spawnX = stoi(sX);
				spawnY = stoi(sY);

				StringEditor::echo(L"spawn X: " + to_wstring(spawnX));
				StringEditor::echo(L"spawn Y: " + to_wstring(spawnY));
				StringEditor::echo(L"spawn D: " + to_wstring(spawnDirection));
			}
			catch (exception e)
			{
				StringEditor::echo(sf::String(e.what()));
			}
		}

		else if (StringEditor::equals(w, L"blocks=["))
		{
			for (int j = 0; j < height; j++)
			{
				file.readLine(w);
				for (int i = 0; i < width; i++)
				{
					int comma = StringEditor::findCharacter(w, L',', 3);
					//0 is inclusive, comma is exclusive
					wstring tile = StringEditor::substring(w, 0, comma);
					map[i][j] = Tile(tile);
					w = StringEditor::substring(w, comma + 1, w.length());
				}
			}
			file.readLine(w);
			//The line above is to ignore the ] that makes the text file look nicer
			continue;
		}

		else if (StringEditor::startsWith(w, L"addTransparentOverhang"))
		{
			int openParenthesis = StringEditor::findCharacter(w, L'(', 1);
			int comma_1 = StringEditor::findCharacter(w, L',', 1);
			int comma_2 = StringEditor::findCharacter(w, L',', 2);
			int closeParenthesis = StringEditor::findCharacter(w, L')', 1);

			wstring sX = StringEditor::substring(w, openParenthesis + 1, comma_1);
			wstring sY = StringEditor::substring(w, comma_1 + 1, comma_2);
			wstring sN = StringEditor::substring(w, comma_2 + 1, closeParenthesis);

			Tile t;
			t.setX(stoi(sX));
			t.setY(stoi(sY));
			t.setImgNum(stoi(sN));

			transparentOverhangTiles.push_back(t);
		}
		else if (StringEditor::equals(w, L"addOpaqueOverhang"))
		{

		}

		else if (StringEditor::equals(w, L"endFile;"))
		{
			break;
		}
	}

	file.close();
	StringEditor::echo(L"file.close()");

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

//=================================================================================================

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
			/*
			
			Stop talking with a character.
			Need to implement longer conversations.
			
			*/
			players[playerNumber].setNPCDialogNumber(-1);
			players[playerNumber].setMode(Player::Mode::NORMAL);
		}
		return;
	}
	else if (players[playerNumber].getMode() == Player::Mode::MENU)
	{
		if (players[playerNumber].getMenu().isRequestingExit())
		{
			players[playerNumber].setMode(Player::Mode::NORMAL);
		}
		if (players[playerNumber].getMenu().getRequestedMode() == InGameMenu::RequestMode::QUIT)
		{
			players[playerNumber].getMenu().setRequestedModeRead();
			rm = RequestMode::MAIN_MENU;
		}
		players[playerNumber].updateMenu(c);
		return;
	}

	if (!players[playerNumber].isLocked())
	{
		//If player is in transition between two blocks
		if (((int)players[playerNumber].getActualX() % 32 == 0) && ((int)players[playerNumber].getActualY() % 32 == 0))
		{
			players[playerNumber].setAnimationFrame(rollOverAdd(players[playerNumber].getAnimationFrame(), 1, 3));
		}

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
			if ((players[playerNumber].getY() == (height - 1))) { downBlocked = true; }
			if ((players[playerNumber].getX() == (width - 1))) { rightBlocked = true; }

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
	for (int x = 0; x < width; x++)
	{
		if (x >= players[playerNumber].getX() - 11 && x <= players[playerNumber].getX() + 11)
		{
			for (int y = 0; y < height; y++)
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
		font.drawText(window, 16, DIALOG_BOX_LOW + 16, npcs[players[playerNumber].getNPCDialogNumber()].getName(players[playerNumber].getLanguageCode()) + L":", to_Color(npcs[players[playerNumber].getNPCDialogNumber()].getSex()));
		font.drawText(window, 16, DIALOG_BOX_LOW + 16 + FONT_SIZE, npcs[players[playerNumber].getNPCDialogNumber()].getDialog(players[playerNumber].getLanguageCode()), sf::Color::Black);
	}

	for (int i = 0; i < transparentOverhangTiles.size(); i++)
	{
		int tx = transparentOverhangTiles[i].getX();
		int ty = transparentOverhangTiles[i].getY();
		int px = players[playerNumber].getX();
		int py = players[playerNumber].getY();

		if (ty >= py - 6 && tx >= px - 10 && ty <= py + 6 && tx <= px + 10)
		{
			sf::View view;
			view.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
			view.setCenter(sf::Vector2f(players[playerNumber].getActualX() + 32, players[playerNumber].getActualY() + 32));
			window.setView(view);

			sf::Sprite s(textures[transparentOverhangTiles[i].getImgNum()]);
			s.setPosition(sf::Vector2f(transparentOverhangTiles[i].getX() * BLOCK_SIZE, transparentOverhangTiles[i].getY() * BLOCK_SIZE));
			window.draw(s);
		}
	}

	//RENDER DEBUG STUFF
	font.coordinates(window, players[playerNumber].getX(), players[playerNumber].getY());


	//RENDER MENU STUFF
	if (players[playerNumber].getMode() == Player::Mode::MENU)
	{
		players[playerNumber].renderMenu(window, font);
	}
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
	if (players[playerNumber].getY() == 0)
	{
		return false;
	}
	for (int i = 0; i < npcs.size(); i++)
	{
		if (npcs[i].getX() == players[playerNumber].getX() && npcs[i].getY() == players[playerNumber].getY() - 1)
		{
			return true;
		}
		if (npcs[i].getX() == players[playerNumber].getX() - 1 && npcs[i].getY() == players[playerNumber].getY() - 1)
		{
			return true;
		}
		if (npcs[i].getX() == players[playerNumber].getX() + 1 && npcs[i].getY() == players[playerNumber].getY() - 1)
		{
			return true;
		}
	}
	return false;
}