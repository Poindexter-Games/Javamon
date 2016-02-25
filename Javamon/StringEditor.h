#pragma once

#include <SFML/System/String.hpp>

#include <string>
#include <iostream>

using namespace std;

/*
Class for parsing strings for scripting language or for shortcuts for displaying to the terminal

Author: Karl Piepho
Date Created: Not going to bother and find out
Date Revised: Feb 2, 2016
*/
class StringEditor
{
public:
	static bool equals(sf::String, wstring);

	/*
	Shortcut method for std::wcout << line << std::endl;

	Author: Karl Piepho
	Date Created: Feb 2,2016
	Date Revised: Feb 2,2016
	*/
	static void echo(wstring);
	/*
	Shortcut method for std::wcout << line << std::endl;

	Author: Karl Piepho
	Date Created: Feb 2,2016
	Date Revised: Feb 2,2016
	*/
	static void echo(int);
	static void echo(float);
	static void echo(wstring, int);
	static void echo(int, wstring);
	/*
	This is for converting the Japanese Hiragana syllabary to the Katakana syllabary.
	Notes: Unimplemented
	*/
	wstring hiraganaToKatakana(wstring);
	/*
	This is for converting the Japanese Katakana syllabary to the Hiragana syllabary.
	Notes: Unimplemented
	*/
	wstring katakanaToHiragana(wstring);
private:
};