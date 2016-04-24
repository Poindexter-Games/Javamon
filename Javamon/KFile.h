#pragma once

#include <locale.h>
#include <fstream>
#include <string>

#include <fcntl.h>
#include <io.h>
#include <codecvt>

#include <SFML/System/String.hpp>

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
	Calls the default getline command provided by namespace std.
	Author: Karl Piepho
	Date Created: March 15, 2016
	Date Revised:
	Revised By:
	*/
	void readLine(wstring&);
	/*
	Closes the file

	Author: Karl Piepho
	Date Created: Feb 7, 2016
	*/
	void close();
private:
	std::wfstream file;
};