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
	Returns the number of segments in a line
	A segment is defined as text between two points a and b
	where a can be a comma or the start of a line
	and where b can be a comma or a semi colon

	Returns -1 if there were no semi colons at the end of the string
	Returns 0 if it was a blank line

	Author: Karl Piepho
	Date Created: Feb 2,2016
	Date Revised: Feb 2,2016
	*/
	static int getNumberOfSegments(wstring);
	/*
	Breaks apart a line from the file reader to be interpreted by any class
	to create some sort of object.

	For Example:
	setWidth,1;

	Author: Karl Piepho
	Date Created: Feb 2,2016
	Date Revised: Feb 3,2016
	*/
	static wstring* breakApart(wstring);
	/*
	Breaks apart of a line from the file reader to be interpreted by any class
	to create some sort of object.

	For Example:
	single_player=Single Player

	This will always return with a wstring array with 2 wstrings

	Author: Karl Piepho
	Date Created: Feb 6, 2016
	Date Revised: Feb 6, 2016
	*/
	static wstring* breakInHalf(wstring);
private:
	/*
	Returns the location of a certain commma or semicolon
	The first comma (or semicolon) is marked as endOfSegmentNumber equaling ZERO

	Returns -2 if the end of segment number was out of range
	Returns -1 for the beginning of the string if(endOfSegment == 0)
	Returns location of comma or semi colon

	Author: Karl Piepho
	Date Created: Feb 2,2016
	Date Revised: Feb 3,2016
	*/
	static int getBreakPosition(wstring, int);
};