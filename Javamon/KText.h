#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/String.hpp>
#include <string>

#include "Variables.h"
#include "Language.h"
#include "StringEditor.h"

using namespace std;

class KText
{
public:
	/*
	This is a default constructor, make sure to override this with KText(Language)
	*/
	KText();
	/*
	This will instantiate the files needed for the language
	*/
	KText(Language);

	/*
	This renders a dialog box on the bottom of the screen for text inside the
	movement portion of the game.
	*/
	void levelDialog(sf::RenderWindow &, wstring);
	/*
	This renders the word loading
	*/
	void simpleMessage(sf::RenderWindow &, wstring);
	/*
	This renders X and Y coordinates
	*/
	void coordinates(sf::RenderWindow &, int, int);
	/*
	This renders text
	*/
	void drawText(sf::RenderWindow &, int, int, sf::String);
private:
	/*
	This is for determining which character sets are needed.
	*/
	Language lang;
	/*
	26 letter latin-alphabet and a few diacritics.
	This is loaded for every language.
	*/
	sf::Texture basic_latin;
	/*
	Basic kana chart for the Japanese language.
	This is loaded only for the Japanese language.
	*/
	sf::Texture japanese;
	/*
	This is an array that holds the widths of the 256 characters in the
	Basic_Latin.png file so that our font is not monospaced in the English version.
	*/
	int* latinWidths;
};