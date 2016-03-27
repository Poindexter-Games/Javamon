#pragma once

#include <locale.h>
#include <fstream>
#include <string>

#include <fcntl.h>
#include <io.h>
#include <codecvt>

#include <SFML/System/String.hpp>

#include "Variables.h"
#include "StringEditor.h"
#include "KFile.h"

class Language
{
public:
	Language();
	/*
	Load a language

	Author: Karl Piepho
	Date Created: February 6, 2016
	Date Revised: February 6, 2016
	*/
	Language(sf::String);

	sf::String getLanguageCode() { return langCode; }
	sf::String getLoading() { return loading; }
	sf::String getQuit() { return quit; }
	sf::String getTrainer() { return trainer; }
	sf::String getMainMenu() { return main_menu; };
	sf::String getBag(){return bag;}
	sf::String getMonster(){return monster;}
	sf::String getMap(){return map;}
	sf::String getPhone(){return phone;}
	sf::String getSave() { return save; }
private:
	sf::String langCode;

	sf::String single_player;
	sf::String multi_player;
	sf::String settings;
	sf::String quit;
	sf::String loading;
	sf::String trainer;
	sf::String main_menu;
	sf::String bag;
	sf::String monster;
	sf::String map;
	sf::String phone;
	sf::String save;
};