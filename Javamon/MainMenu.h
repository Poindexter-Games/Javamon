#pragma once

#include "Screen.h"

#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\Texture.hpp>

#include "Variables.h"
#include "StringEditor.h"
#include "Language.h"
#include "KText.h"

class MainMenu : public Screen
{
public:
	enum RequestMode { SINGLE_PLAYER, MULTI_PLAYER, OPTIONS, QUIT, NONE };

	MainMenu();
	MainMenu(Language);
	void update(Controls&);
	void render(sf::RenderWindow&);

	RequestMode getRequestedMode() { return m; }
	void setRequestedModeRead() { m = RequestMode::NONE; }
private:
	int boxSelected = 0;

	RequestMode m;

	sf::Texture logoTexture;

	sf::RectangleShape singleplayer;
	sf::RectangleShape multiplayer;
	sf::RectangleShape options;
	sf::RectangleShape quit;
};