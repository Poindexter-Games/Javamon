#include "MainMenu.h"

MainMenu::MainMenu():Screen(Language())
{

}

MainMenu::MainMenu(Language l):Screen(l)
{
	if (StringEditor::equals(l.getLanguageCode(), L"ja_JP"))
	{
		logoTexture.loadFromFile(VIDEO + "TitleJP.png");
	}
	else
	{
		logoTexture.loadFromFile(VIDEO + "Title.png");
	}

	sf::Texture * texture = &logoTexture;

	logo = sf::RectangleShape(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	logo.setTexture(texture);
	logo.setPosition(sf::Vector2f(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4));

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

void MainMenu::render(sf::RenderWindow & w)
{
	w.draw(logo);

	w.draw(singleplayer);
	w.draw(multiplayer);
	w.draw(options);
	w.draw(quit);
}