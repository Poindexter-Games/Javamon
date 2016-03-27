#include "InGameMenu.h"

InGameMenu::InGameMenu()
{
	boxSelected = 0;

	box = sf::Texture();
	box.loadFromFile(VIDEO + "SideBar.png", sf::IntRect(0, 0, SIDE_BAR_WIDTH, SIDE_BAR_BOX_HEIGHT));

	selector = sf::Texture();
	selector.loadFromFile(VIDEO + "SideBar.png", sf::IntRect(0, 90, SIDE_BAR_WIDTH, SIDE_BAR_BOX_HEIGHT));

	state = State::DEFAULT;
}

void InGameMenu::setLanguage(Language l)
{
	InGameMenu::l = l;
}

void InGameMenu::update(Controls & c)
{
	requestsExit = false;

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
			requestsExit = true;
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
				requestsExit = true;
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
				//TO DO, GO TO MAIN MENU
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

void InGameMenu::render(sf::RenderWindow & window, KText& font)
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
			s.setTexture(selector);
			s.setPosition(sf::Vector2f(SIDE_BAR_X, SIDE_BAR_BOX_HEIGHT * boxSelected));
			window.draw(s);
		}

		if (state == MAIN_MENU)
		{
			//Override the usual side bar selector to look as if it is still displayed on the main menu button
			sf::Sprite s;
			s.setTexture(selector);
			s.setPosition(sf::Vector2f(SIDE_BAR_X, SIDE_BAR_BOX_HEIGHT * 6));
			window.draw(s);

			//Background of the pop-up box, TO DO
			sf::RectangleShape bg;
			bg.setFillColor(sf::Color(255, 159, 0, 255));
			bg.setPosition(sf::Vector2f(SCREEN_WIDTH * 3 / 8, SCREEN_HEIGHT * 3 / 8));
			bg.setSize(sf::Vector2f(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4));
			window.draw(bg);
		}
	}
	else if (state == State::PLAYER)
	{
		sf::RectangleShape bg;
		bg.setFillColor(sf::Color(255, 95, 0, 255));
		bg.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		window.draw(bg);
	}
}

bool InGameMenu::isRequestingExit()
{
	return requestsExit;
}
