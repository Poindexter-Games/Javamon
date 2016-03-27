#pragma once

#include "Screen.h"

#include "Math.h"

#include "Controls.h"
#include "Variables.h"
#include "SFML/Graphics/RenderWindow.hpp"

#include "KText.h"
#include "StringEditor.h"



class InGameMenu: public Screen
{
public:
	/*
	Default: Main in Game Menu
	Player: Menu to display player stuff
	Save: Asks if you want to save
	Main Menu: Pop-up box asking if you really want to return to the main menu.
	
	*/
	enum State{DEFAULT, PLAYER, MAIN_MENU};

	InGameMenu();
	void setLanguage(Language l);
	void update(Controls&);
	void render(sf::RenderWindow&, KText&);
	bool isRequestingExit();
private:
	Language l;

	sf::Texture box;
	sf::Texture selector;
	int boxSelected;
	bool requestsExit = false;

	State state;
};