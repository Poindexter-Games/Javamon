#include "MainMenu.h"

MainMenu::MainMenu()
{

}

MainMenu::MainMenu(Language l)
{
	m = RequestMode::NONE;
	boxSelected = 0;

	logoTexture = sf::Texture();

	if (StringEditor::equals(l.getLanguageCode(), L"ja-JP"))
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
	if (c.isPressedForFirstTime(Control::C_UP))
		boxSelected = 0;
	if (c.isPressedForFirstTime(Control::C_LEFT))
		boxSelected = 1;
	if (c.isPressedForFirstTime(Control::C_DOWN))
		boxSelected = 2;
	if (c.isPressedForFirstTime(Control::C_RIGHT))
		boxSelected = 3;
	if (c.isPressedForFirstTime(Control::ACCEPT))
	{
		if (boxSelected == 0)
		{
			m = RequestMode::SINGLE_PLAYER;
		}
		else if (boxSelected == 1)
		{
			m = RequestMode::QUIT;
		}
		else if (boxSelected == 2)
		{
			m = RequestMode::OPTIONS;
		}
		else if (boxSelected == 3)
		{
			m = RequestMode::MULTI_PLAYER;
		}
	}
}

void MainMenu::render(sf::RenderWindow & w)
{
	sf::Sprite s;
	s.setPosition(sf::Vector2f(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4));
	s.setTexture(logoTexture);

	if (boxSelected == 0)
		singleplayer.setFillColor(sf::Color(0, 255, 255));
	else singleplayer.setFillColor(sf::Color(64, 64, 64));

	if (boxSelected == 1)
		quit.setFillColor(sf::Color(0, 255, 255));
	else quit.setFillColor(sf::Color(64, 64, 64));

	if (boxSelected == 2)
		options.setFillColor(sf::Color(0, 255, 255));
	else options.setFillColor(sf::Color(64, 64, 64));

	if (boxSelected == 3)
		multiplayer.setFillColor(sf::Color(0, 255, 255));
	else multiplayer.setFillColor(sf::Color(64, 64, 64));

	w.draw(s);

	w.draw(singleplayer);
	w.draw(multiplayer);
	w.draw(options);
	w.draw(quit);
}