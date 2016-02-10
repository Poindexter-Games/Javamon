#include "KFile.h"

KFile::KFile(sf::String filepath)
{
	std::locale locale("");											//This will read the user's locale, so the program can determine string encoding since wifstream uses a regular string to load a file
	std::string path = sf::String(filepath).toAnsiString(locale);	//This translates sf::String to std::string so that std::wfstream can be opened
	
	file.open(path);

	//This is to load the file as a UTF-8 format
	file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>()));

	std::wstring line;
	getline(file, line);
	/*These two lines ignore the first line of the file which contain the BOM character

	Quote from Wikipedia (https://en.wikipedia.org/wiki/Byte_order_mark):
	The UTF-8 representation of the BOM is the byte sequence 0xEF,0xBB,0xBF.
	A text editor or web browser misinterpreting the text as ISO-8859-1 or CP1252
	will display the characters ﻿ for this.

	Karl: I'm just to lazy to create a thing to ignore the first line of text file,
	but later we should create some code to ignore it.
	*/
}

bool KFile::readLine(sf::String *& strings, int & length)
{
	std::wstring str;
	getline(file, str);

	int type = 0;		//Format type

	int SCRIPT = 1;		//If the line has this format - setWidth(8)
	int VARIABLE = 2;	//If the line has this format - width = 8

	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == L'=') { type = VARIABLE; break; }
		if (str[i] == L',' || str[i] == L';' || str[i] == L'(') { type = SCRIPT; break; }
	}

	if (type == SCRIPT)
	{
		length = getNumberOfSegments(str);
		strings = breakApart(str);

		return true;

	}
	else if (type == VARIABLE)
	{
		length = 2;
		strings = breakInHalf(str);

		return true;
	}


	/*
	File read error means that the line did not follow an acceptable format.
	Example formats are the script and variable formats

	Script:
	setTelepor(0,x,y,to,x,y,dir,zdir)
	
	Variable:
	upButton = w
	leftButton = a
	downButton = s
	rightButton = d

	Mixed:
	createNPC();	//This will have an argument of 1 for npc if we do not learn how to use vectors
	name = John Smith
	dialog = It's nice weather out!\nHow are you doing today?
	endCreateNPC();
	*/
	length = 1;
	strings = new sf::String[length]{ L"FileReadError" };

	return false;
}

void KFile::close()
{
	file.close();
}

int KFile::getBreakPosition(sf::String str, int endOfSegmentNumber)
{
	if (endOfSegmentNumber == 0) return -1;
	int s = 0;
	for (int i = 0; i < str.toWideString().length(); i++)
	{
		if (str[i] == L',' || str[i] == L';' || str[i] == L'(' || str[i] == L')')
		{
			s++;
			if (s == endOfSegmentNumber)
			{
				return i;
			}
		}
	}
	//This means that the segment number was invalid
	return -2;
}

int KFile::getNumberOfSegments(sf::String str)
{
	if (str.toWideString().length() == 0)
		return 0;


	int num = 0;
	for (int i = 0; i < str.toWideString().length(); i++)
	{
		if (str[i] == L'(')
		{
			num++;
		}
		else if (str[i] == L',')
		{
			num++;
		}
		if (str[i] == L')')
		{
			num++;
			return num;
		}
		else if (str[i] == L';')
		{
			num++;
			return num;
		}
	}
	/*
	If the program gets this far into the function, we know the user did not end a line with a semi colon
	It would be the same difficulty to program the game to not use semicolons as it would be to use semi colons,
	but either way, we must be consistent, and I have chosen to use semi colons for now as it justs looks interesting :)
	-Karl Piepho
	*/
	return -1;
}

sf::String* KFile::breakApart(sf::String str)
{
	if (str.toWideString().compare(L"endFile;") == 0) return new sf::String[1]{ L"endFile"};
	if (str.toWideString().compare(L"endFile();") == 0) return new sf::String[1]{ L"endFile"};
	int s = getNumberOfSegments(str);
	sf::String* strs = new sf::String[s];
	for (int i = 0; i < s; i++)
	{
		int pos0 = getBreakPosition(str, i);
		int pos1 = getBreakPosition(str, i + 1);
		strs[i] = str.toWideString().substr(pos0 + 1, (pos1 - 1) - (pos0));
	}
	return strs;
}
sf::String* KFile::breakInHalf(sf::String str)
{
	if (str.toWideString().compare(L"endFile;") == 0) return new sf::String[2]{ L"endFile", L"" };
	if (str.toWideString().compare(L"endFile();") == 0) return new sf::String[2]{ L"endFile", L"" };
	int pos = str.find(L'=');
	sf::String* strs = new sf::String[2];
	strs[0] = str.toWideString().substr(0, pos);
	strs[1] = str.toWideString().substr(pos + 1, str.toWideString().length() - (pos + 1));
	return strs;
}