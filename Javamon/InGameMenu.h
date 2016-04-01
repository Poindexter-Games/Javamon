#pragma once

#include "Screen.h"

#include "Math.h"

#include "Controls.h"
#include "Variables.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "Monster.h"
#include "MonsterStats.h"
#include "KText.h"
#include "StringEditor.h"

class InGameMenu: public Screen
{
public:
	enum RequestMode {QUIT, NONE};
	RequestMode getRequestedMode() { return rm; }
	void setRequestedModeRead() { rm = RequestMode::NONE; }

	/*
	Default: Main in Game Menu
	Player: Menu to display player stuff
	Bag: Menu to displayer stuff in the player's bag
	Party: Display's the players monsters
	Save: Asks if you want to save
	Main Menu: Pop-up box asking if you really want to return to the main menu.
	
	*/
	enum State{DEFAULT, PLAYER, BAG, PARTY, MAIN_MENU};

	InGameMenu();
	void setLanguage(Language l);
	void update(Controls&, BattleType, vector<Monster>);
	void render(sf::RenderWindow&, KText&, sf::String, Sex, BattleType, vector<Monster>);
	bool isRequestingExit();
private:
	RequestMode rm;
	Language l;

	sf::Texture box;
	sf::Texture boxSelector;

	sf::Texture singleMale;
	sf::Texture singleFemale;
	sf::Texture singleSelector;
	sf::Texture singleNeuter;

	sf::Texture doubleMale;
	sf::Texture doubleFemale;
	sf::Texture doubleSelector;
	sf::Texture doubleNeuter;

	sf::Texture questionWindow;
	sf::Texture questionBox;
	sf::Texture questionSelector;

	int boxSelected;
	bool requestsExit = false;

	State state;
};