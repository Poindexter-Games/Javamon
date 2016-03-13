#include "MainMenu.h"

MainMenu::MainMenu()
{

}

MainMenu::MainMenu(Language l)
{
	logoTexture = sf::Texture();

	if (StringEditor::equals(l.getLanguageCode(), L"ja_JP"))
	{
		logoTexture.loadFromFile(VIDEO + "TitleJP.png");
	}
	else
	{
		logoTexture.loadFromFile(VIDEO + "Title.png");
	}

	singleplayer = sf::RectangleShape(sf::Vector2f(SCREEN_WIDTH  / 8, SCREEN_HEIGHT / 36));
	multiplayer  = sf::RectangleShape(sf::Vector2f(SCREEN_HEIGHT / 36, SCREEN_WIDTH  / 8));
	options      = sf::RectangleShape(sf::Vector2f(SCREEN_WIDTH  / 8, SCREEN_HEIGHT / 36));
	quit         = sf::RectangleShape(sf::Vector2f(SCREEN_HEIGHT / 36, SCREEN_WIDTH  / 8));

	singleplayer.setFillColor(sf::Color(64, 64, 64));
	multiplayer.setFillColor(sf::Color(64, 64, 64));
	options.setFillColor(sf::Color(64, 64, 64));
	quit.setFillColor(sf::Color(64, 64, 64));

	//setPositions
	singleplayer.setPosition(sf::Vector2f((.5 * SCREEN_WIDTH) - (.5 * singleplayer.getSize().x), 0));
	multiplayer.setPosition(sf::Vector2f(SCREEN_WIDTH - multiplayer.getSize().x, (.5 * SCREEN_HEIGHT) - (.5 * multiplayer.getSize().y)));
	options.setPosition(sf::Vector2f((.5 * SCREEN_WIDTH) - (.5 * options.getSize().x), SCREEN_HEIGHT - options.getSize().y));
	quit.setPosition(sf::Vector2f(0, (.5 * SCREEN_HEIGHT) - (.5 * quit.getSize().y)));
}

void MainMenu::update(Controls & c)
{
	if((c.isPressedForFirstTime(Control::MOUSE_LEFT) /*&& mouse is in rect*/ ) || c.isPressedForFirstTime(Control::C_UP))
	{
		//goto single player
	}
}

void MainMenu::render(sf::RenderWindow & w)
{
	sf::Sprite s;
	s.setPosition(sf::Vector2f(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4));
	s.setTexture(logoTexture);

	w.draw(s);

	w.draw(singleplayer);
	w.draw(multiplayer);
	w.draw(options);
	w.draw(quit);
}