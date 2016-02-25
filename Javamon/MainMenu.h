#pragma once

#include "Screen.h"

#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\Texture.hpp>

#include "Variables.h"
#include "StringEditor.h"
#include "Language.h"
#include "KText.h"

class MainMenu: public Screen
{
public:
	MainMenu();
	MainMenu(Language);
	void render(sf::RenderWindow & w);
private:
	sf::RectangleShape logo;
	sf::Texture logoTexture;

	sf::RectangleShape singleplayer;
	sf::RectangleShape multiplayer;
	sf::RectangleShape options;
	sf::RectangleShape quit;
};
