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

class KFile
{
public:
	/*
	Loads a file
	Example:
	Resources/Languages/en_US.txt
	REMEMBER TO CLOSE A FILE

	Author: Karl Piepho
	Date Created: Feb 7, 2016
	Date Revised: Feb 9, 2016
	Revised By: Karl Piepho
	*/
	KFile(sf::String);
	/*
	Reads a line from the file
	and sets strings to the parameters of the line
	and length to the number of parameters in the
	strings array.

	Author: Karl Piepho
	Date Created: Feb 7, 2016
	Date Revised: Feb 20, 2016
	Revised By: Karl Piepho
	*/
	bool readLine(sf::String* &, int &);
	/*
	Closes the file

	Author: Karl Piepho
	Date Created: Feb 7, 2016
	*/
	void close();
private:
	std::wfstream file;
	/*
	Returns the number of segments in a line
	A segment is defined as text between two points a and b
	where a can be a comma or the start of a line
	and where b can be a comma or a semi colon

	Returns -1 if there were no semi colons at the end of the string
	Returns 0 if it was a blank line

	Author: Karl Piepho
	Date Created: Feb 7,2016
	Date Revised: Feb 7,2016
	*/
	static int getNumberOfSegments(sf::String);
	/*
	Breaks apart a line from the file reader to be interpreted by any class
	to create some sort of object.

	For Example:
	setWidth,1;

	Author: Karl Piepho
	Date Created: Feb 7,2016
	Date Revised: Feb 7,2016
	*/
	static sf::String* breakApart(sf::String);
	/*
	Breaks apart of a line from the file reader to be interpreted by any class
	to create some sort of object.

	For Example:
	single_player=Single Player

	This will return a string with 2 or 3 strings depending if the user added a language tag
	If the bool is true, the program will look out for the language tag.
	If false, the program will not split the variable and it's language tag.

	Author: Karl Piepho
	Date Created: Feb 7, 2016
	Date Revised: Feb 20, 2016
	*/
	static sf::String* breakInHalf(sf::String, bool);
	/*
	Returns the location of a certain commma or semicolon
	The first comma (or parenthesis, or semicolon) is marked as endOfSegmentNumber equaling ZERO

	Returns -2 if the end of segment number was out of range
	Returns -1 for the beginning of the string if(endOfSegment == 0)
	Returns location of comma or semi colon

	Author: Karl Piepho
	Date Created: Feb 7,2016
	Date Revised: Feb 7,2016
	*/
	static int getBreakPosition(sf::String, int);
};