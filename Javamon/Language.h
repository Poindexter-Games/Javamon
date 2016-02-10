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
private:
	sf::String langCode;

	sf::String single_player;
	sf::String multi_player;
	sf::String settings;
	sf::String quit;
	sf::String loading;
};