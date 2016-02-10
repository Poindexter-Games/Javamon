#include "Language.h"

Language::Language(sf::String str)
{
	langCode = str;

	/*
	OLD CODE, MOVED TO KFILE

	std::locale locale("");					//This will read the user's locale, so the program can determine string encoding since wifstream uses a regular string to load a file
	StringEditor::echo(sf::String(locale.name()).toWideString());
	std::string path = sf::String(RESOURCES + L"Languages/" + str + L".txt").toAnsiString(locale);
	
	std::wifstream file;
	file.open(path);

	std::wstring line;			//This is the file of the line
	getline(file, line);		//This is to ignore the first line of the file, which contains the BOM character
	wstring* segments = new wstring[2];

	file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, consume_header>()));
	*/

	KFile file(RESOURCES + L"Languages/" + str + L".txt");
	sf::String* segments;
	int length;

	for (bool b = true; b; )
	{
		file.readLine(segments, length);

		for (int i = 0; i < length; i++)
		{
			StringEditor::echo(segments[i]);
		}

		if (segments[0].toWideString().compare(L"single_player") == 0) { single_player = sf::String(segments[1]); }
		if (segments[0].toWideString().compare(L"multi_player") == 0) { multi_player = sf::String(segments[1]); }
		if (segments[0].toWideString().compare(L"settings") == 0) { settings = sf::String(segments[1]); }
		if (segments[0].toWideString().compare(L"quit") == 0) { quit = sf::String(segments[1]); }
		if (segments[0].toWideString().compare(L"loading") == 0) { loading = sf::String(segments[1]); }

		if (segments[0].toWideString().compare(L"endFile") == 0)
		{
			b = false;
		}
	}
	file.close();
}

Language::Language()
{
	//This is in case the language somehow is not loaded
	langCode = L"en_US";
	
	single_player = L"Single Player";
	multi_player = L"Multi Player";
	settings = L"Settings";
	quit = L"Quit";
	loading = L"Loading...";
}