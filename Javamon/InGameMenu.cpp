#include "InGameMenu.h"

InGameMenu::InGameMenu()
{
	m = RequestMode::NONE;
	boxSelected = 0;

	box = sf::Texture();
	boxSelector = sf::Texture();
	box.loadFromFile(VIDEO + "Boxes.png", sf::IntRect(0, 0, 288, 90));
	boxSelector.loadFromFile(VIDEO + "Boxes.png", sf::IntRect(288, 0, 288, 90));

	singleMale = sf::Texture();
	singleFemale = sf::Texture();
	singleSelector = sf::Texture();
	singleNeuter = sf::Texture();
	singleMale.loadFromFile(VIDEO + "Boxes.png",		sf::IntRect(288 * 0, 90, 288, 144));
	singleFemale.loadFromFile(VIDEO + "Boxes.png",		sf::IntRect(288 * 1, 90, 288, 144));
	singleSelector.loadFromFile(VIDEO + "Boxes.png",	sf::IntRect(288 * 2, 90, 288, 144));
	singleNeuter.loadFromFile(VIDEO + "Boxes.png",		sf::IntRect(288 * 3, 90, 288, 144));

	doubleMale = sf::Texture();
	doubleFemale = sf::Texture();
	doubleSelector = sf::Texture();
	doubleNeuter = sf::Texture();
	doubleMale.loadFromFile(VIDEO + "Boxes.png",		sf::IntRect(360 * 0, 234, 360, 180));
	doubleFemale.loadFromFile(VIDEO + "Boxes.png",		sf::IntRect(360 * 1, 234, 360, 180));
	doubleSelector.loadFromFile(VIDEO + "Boxes.png",	sf::IntRect(360 * 2, 360, 288, 180));
	doubleNeuter.loadFromFile(VIDEO + "Boxes.png",		sf::IntRect(360 * 3, 234, 360, 180));

	/*We need to fix the sizes for QuestionBox.png*/
	questionWindow = sf::Texture();
	questionBox = sf::Texture();
	questionSelector = sf::Texture();
	questionWindow.loadFromFile(VIDEO + "QuestionBox.png",		sf::IntRect(0, 0, 640, 360));
	questionBox.loadFromFile(VIDEO + "QuestionBox.png",			sf::IntRect(640, 42 * 0, 320, 42));
	questionSelector.loadFromFile(VIDEO + "QuestionBox.png",	sf::IntRect(640, 42 * 1, 320, 42));

	state = State::DEFAULT;
}

void InGameMenu::setLanguage(Language l)
{
	InGameMenu::l = l;
}

void InGameMenu::update(Controls & c, BattleType bt, vector<Monster> party)
{
	m = RequestMode::NONE;

	if (state == State::DEFAULT)
	{
		if (c.isPressedForFirstTime(Control::C_DOWN))
		{
			boxSelected = rollOverAdd(boxSelected, 0, NUM_OF_SIDE_BAR_BOXES - 1, 1);
		}
		else if (c.isPressedForFirstTime(Control::C_UP))
		{
			boxSelected = rollOverAdd(boxSelected, 0, NUM_OF_SIDE_BAR_BOXES - 1, -1);
		}
		else if (c.isPressedForFirstTime(Control::CANCEL) || c.isPressedForFirstTime(Control::START))
		{
			//m = RequestMode::CLOSE;
		}
		else if (c.isPressedForFirstTime(Control::ACCEPT))
		{
			if (boxSelected == 0)
			{
				//player
				state = State::PLAYER;
			}
			else if (boxSelected == 1)
			{
				//bag
			}
			else if (boxSelected == 2)
			{
				//party
				state = State::PARTY;
				boxSelected = 0;
			}
			else if (boxSelected == 3)
			{
				//map
			}
			else if (boxSelected == 4)
			{
				//phone
			}
			else if (boxSelected == 5)
			{
				//save
			}
			else if (boxSelected == 6)
			{
				//main menu
				state = State::MAIN_MENU;
				boxSelected = 1; //0 is yes, 1 is no
			}
			else if (boxSelected == 7)
			{
				//quit
				//m = RequestMode::CLOSE;
			}
		}
	}
	else if (state == State::PLAYER)
	{
		if(c.isPressedForFirstTime(Control::CANCEL))
		{
			state = State::DEFAULT;
		}
	}
	else if (state == State::BAG)
	{
		if (c.isPressedForFirstTime(Control::CANCEL))
		{
			state = State::DEFAULT;
		}
	}
	else if (state == State::PARTY)
	{
		if (c.isPressedForFirstTime(Control::CANCEL))
		{
			state = State::DEFAULT;
			boxSelected = 2;
		}
		if (c.isPressedForFirstTime(Control::C_UP))
		{
			boxSelected = rollOverAdd(boxSelected, 0, party.size() - 1, -1);
		}
		else if (c.isPressedForFirstTime(Control::C_DOWN))
		{
			boxSelected = rollOverAdd(boxSelected, 0, party.size() - 1, 1);
		}
	}
	else if (state == MAIN_MENU)
	{
		if (c.isPressedForFirstTime(Control::CANCEL))
		{
			state = State::DEFAULT;
			boxSelected = 6;
		}
		else if (c.isPressedForFirstTime(Control::ACCEPT))
		{
			if (boxSelected == 0)
			{
				m = RequestMode::QUIT;
			}
			else
			{
				state = State::DEFAULT;
				boxSelected = 6;
			}
		}
		if (c.isPressedForFirstTime(Control::C_LEFT))
		{
			boxSelected = rollOverAdd(boxSelected, 0, 1, -1);
		}
		else if (c.isPressedForFirstTime(Control::C_RIGHT))
		{
			boxSelected = rollOverAdd(boxSelected, 0, 1, 1);
		}
	}
	
}

void InGameMenu::render(sf::RenderWindow & window, KText& font, sf::String name, Sex s, BattleType bt, vector<Monster> party)
{
	if (state == State::DEFAULT || state == State::MAIN_MENU)
	{
		for (int i = 0; i < NUM_OF_SIDE_BAR_BOXES; i++)
		{
			sf::Sprite s;
			s.setTexture(box);
			s.setPosition(sf::Vector2f(SIDE_BAR_X, SIDE_BAR_BOX_HEIGHT * i));
			window.draw(s);
		}

		font.drawText(window, SIDE_BAR_X + 9, SIDE_BAR_BOX_HEIGHT * 0 + 9, l.getTrainer(), sf::Color::White);
		font.drawText(window, SIDE_BAR_X + 9, SIDE_BAR_BOX_HEIGHT * 1 + 9, l.getBag(), sf::Color::White);
		font.drawText(window, SIDE_BAR_X + 9, SIDE_BAR_BOX_HEIGHT * 2 + 9, l.getMonster(), sf::Color::White);
		font.drawText(window, SIDE_BAR_X + 9, SIDE_BAR_BOX_HEIGHT * 3 + 9, l.getMap(), sf::Color::White);
		font.drawText(window, SIDE_BAR_X + 9, SIDE_BAR_BOX_HEIGHT * 4 + 9, l.getPhone(), sf::Color::White);
		font.drawText(window, SIDE_BAR_X + 9, SIDE_BAR_BOX_HEIGHT * 5 + 9, l.getSave(), sf::Color::White);
		font.drawText(window, SIDE_BAR_X + 9, SIDE_BAR_BOX_HEIGHT * 6 + 9, l.getMainMenu(), sf::Color::White);
		font.drawText(window, SIDE_BAR_X + 9, SIDE_BAR_BOX_HEIGHT * 7 + 9, l.getQuit(), sf::Color::White);

		if (state != State::MAIN_MENU)
		{
			//If the main menu pop-up box is open, do not display the side bar selector
			//as it also used by the main menu selector
			sf::Sprite s;
			s.setTexture(boxSelector);
			s.setPosition(sf::Vector2f(SIDE_BAR_X, SIDE_BAR_BOX_HEIGHT * boxSelected));
			window.draw(s);
		}

		if (state == MAIN_MENU)
		{
			//Override the usual side bar selector to look as if it is still displayed on the main menu button
			sf::Sprite s;
			s.setTexture(boxSelector);
			s.setPosition(sf::Vector2f(SIDE_BAR_X, SIDE_BAR_BOX_HEIGHT * 6));
			window.draw(s);

			//Background of the pop-up box, TO DO
			sf::RectangleShape bg;
			bg.setFillColor(sf::Color(64, 64, 64, 255));
			bg.setPosition(sf::Vector2f(SCREEN_WIDTH * 3 / 8, SCREEN_HEIGHT * 3 / 8));
			bg.setSize(sf::Vector2f(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4));
			window.draw(bg);

			if (StringEditor::equals(l.getLanguageCode(), L"ja-JP"))
			{
				font.drawText(window, SCREEN_WIDTH * 3 / 8, SCREEN_HEIGHT * 3 / 8, to_wstring(boxSelected), sf::Color::Cyan);
				font.drawText(window, SCREEN_WIDTH * 3 / 8, SCREEN_HEIGHT * 3 / 8, L" <--\\n0=main menu ni modoru\\n1=game ni modoru\\nhidari=--\\nmigi=++", sf::Color::White);
			}
			else
			{
				//Temp stuff
				font.drawText(window, SCREEN_WIDTH * 3 / 8, SCREEN_HEIGHT * 3 / 8, to_wstring(boxSelected), sf::Color::Cyan);
				font.drawText(window, SCREEN_WIDTH * 3 / 8, SCREEN_HEIGHT * 3 / 8, L"   <--\\n0 = return to main menu\\n1 = close\\nLeft = --\\nRight = ++", sf::Color::White);
			}

			//Yes box and no box, add the selector too
		}
	}
	else if (state == State::PLAYER)
	{
		sf::RectangleShape bg;
		if (s == Sex::MALE)
		{
			bg.setFillColor(sf::Color(0, 38, 255));
		}
		else
		{
			bg.setFillColor(sf::Color(255, 2, 220));
		}
		bg.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		window.draw(bg);

		font.drawText(window, 0, 0, name, sf::Color::White);
	}
	else if (state == State::PARTY)
	{
		sf::RectangleShape bg;
		bg.setFillColor(sf::Color::Black);
		bg.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		window.draw(bg);

		/*Create an array of x and y co-ordinates for the multiple
		monster boxes so we can use an array to scroll through them*/
		float x [] {   0.0f, 288.0f, 288.0f, 288.0f, 288.0f, 288.0f };
		float y [] { 288.0f,   0.0f, 144.0f, 288.0f, 432.0f, 576.0f };
		if(bt == BattleType::DOUBLE)
		{
			x[0] =   0.0f;
			y[0] = 180.0f;

			x[1] =   0.0f;
			y[1] = 360.0f;

			x[2] = 360.0f;
			y[2] =   0.0f;

			x[3] = 360.0f;
			y[3] = 180.0f;

			x[4] = 360.0f;
			y[4] = 360.0f;

			x[5] = 360.0f;
			y[5] = 540.0f;
		}
		for (int i = 0; i < 6; i++)
		{
			sf::Sprite box;
			if (i < party.size())
			{
				if (party[i].getSex() == Sex::MALE)
				{
					if (bt == BattleType::SINGLE)
					{
						box.setTexture(singleMale);
					}
					else
					{
						box.setTexture(doubleMale);
					}
				}
				else
				{
					if (bt == BattleType::SINGLE)
					{
						box.setTexture(singleFemale);
					}
					else
					{
						box.setTexture(doubleFemale);
					}
				}
			}
			else
			{
				if (bt == BattleType::SINGLE)
				{
					box.setTexture(singleNeuter);
				}
				else
				{
					box.setTexture(doubleNeuter);
				}
			}
			
			box.setPosition(sf::Vector2f(x[i], y[i]));
			window.draw(box);
			if (i < party.size())
			{
				font.drawText(window, x[i] + 8, y[i] + 8, party[i].getName(), sf::Color::White);
				font.drawText(window, x[i] + 8, y[i] + FONT_SIZE + 8, "HP: " + to_string(party[i].getHealth()) + " / " + to_string(party[i].getStats().getHealth()), sf::Color::White);
			}
		}
		sf::Sprite selector;
		if (bt == BattleType::SINGLE)
			selector.setTexture(singleSelector);
		else selector.setTexture(doubleSelector);
		selector.setPosition(x[boxSelected], y[boxSelected]);
		window.draw(selector);
	}
}

bool InGameMenu::isRequestingExit()
{
	return m == RequestMode::CLOSE;
}
