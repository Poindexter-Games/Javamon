#include "InGameMenu.h"

InGameMenu::InGameMenu()
{

}

void InGameMenu::render(sf::RenderWindow & window)
{
	sf::RectangleShape bg;
	bg.setSize(sf::Vector2f(SCREEN_WIDTH / 9 * 40, SCREEN_HEIGHT));
	bg.setPosition(sf::Vector2f(SCREEN_WIDTH - bg.getSize().x, 0));
	bg.setFillColor(sf::Color::Cyan);
	window.draw(bg);
}
