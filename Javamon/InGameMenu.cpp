#include "InGameMenu.h"

InGameMenu::InGameMenu()
{
	boxSelected = 0;

	box = sf::Texture();
	box.loadFromFile(VIDEO + "SideBar.png", sf::IntRect(0, 0, SIDE_BAR_WIDTH, SIDE_BAR_BOX_HEIGHT));

	selector = sf::Texture();
	selector.loadFromFile(VIDEO + "SideBar.png", sf::IntRect(0, 90, SIDE_BAR_WIDTH, SIDE_BAR_BOX_HEIGHT));
}

void InGameMenu::update(Controls & c)
{
	if (c.isPressedForFirstTime(Control::C_DOWN))
	{
		boxSelected = rollOverAdd(boxSelected, 0, NUM_OF_SIDE_BAR_BOXES - 1, 1);
	}
	else if (c.isPressedForFirstTime(Control::C_UP))
	{
		boxSelected = rollOverAdd(boxSelected, 0, NUM_OF_SIDE_BAR_BOXES - 1, -1);
	}
}

void InGameMenu::render(sf::RenderWindow & window)
{
	for (int i = 0; i < NUM_OF_SIDE_BAR_BOXES; i++)
	{
		sf::Sprite s;
		s.setTexture(box);
		s.setPosition(sf::Vector2f(SIDE_BAR_X, SIDE_BAR_BOX_HEIGHT * i));
		window.draw(s);
	}

	sf::Sprite s;
	s.setTexture(selector);
	s.setPosition(sf::Vector2f(SIDE_BAR_X, SIDE_BAR_BOX_HEIGHT * boxSelected));
	window.draw(s);
}
