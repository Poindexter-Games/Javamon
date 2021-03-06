#pragma once
#ifndef _GAME_H_
#define _GAME_H_
//	Libraries
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <SFML/Window/Keyboard.hpp>
#include <io.h>		//These are for outputting utf-8
#include <fcntl.h>	//characters to the command prompt
#include <cstdint>

//	Project Includes
#include "Variables.h"
#include "Controls.h"
#include "Language.h"
#include "KText.h"
#include "MainMenu.h"
#include "Events.h"
#include "Singleplayer.h"
#include "Battle.h"

#endif

class Main
{
public:
	Main(sf::RenderWindow&);
	void update();
	void render();
private:
	sf::RenderWindow & window;
	Language l;
	KText font;
	bool playingGame;

	sf::Event event;
	Events eventHandler;
	Controls controls;

	GameState gs;
	MainMenu mainMenu;
	Singleplayer sp;

	sf::RectangleShape bg;
};