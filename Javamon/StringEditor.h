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
	static wstring hiraganaToKatakana(wstring);
	/*
	This is for converting the Japanese Katakana syllabary to the Hiragana syllabary.
	Notes: Unimplemented
	*/
	static wstring katakanaToHiragana(wstring);

	static int getFirstAppearanceIn(wstring, wchar_t);

	/*
	Returns a substring the begins at begin index and ends with the character before endindex
	beginIndex --> endIndex - 1
	StringEditor::subString("Hello, World!", 7, 12) will return "World"

	Author: Karl Piepho
	Date Created: April 24, 2016
	Date Revised:
	Revised by:
	*/
	static wstring substring(wstring, int, int);

	static bool startsWith(wstring, wstring);

	/*
	Finds the the specified character's position in the string

	Parameters:
	wstring	- the string
	wchar_t	- the character to look for
	int		- the occurence number in the string (1 for the 1st wchar_t)

	Returns:
	The character's position, or -1 if not found.

	Author: Karl Piepho
	Date Created: April 24, 2016
	Date Revised:
	Revised by:
	*/
	static int findCharacter(wstring, wchar_t, int);
private:
};
