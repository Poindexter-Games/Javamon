#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include <iostream>

#include "Variables.h"

using namespace std;

class KText
{
private:
	Language lang; //This will determine how many leters are loaded
	sf::Texture basic_latin;
	sf::Texture japanese;
	int* latinWidths;
public:
	KText(Language); //This will instantiate the texture stuff

	void levelDialog(sf::RenderWindow &, wstring);

	wstring hiraganaToKatakana(wstring);
	wstring katakanaToHiragana(wstring);
};