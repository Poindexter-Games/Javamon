#include "Language.h"

Language::Language(sf::String str)
{
	langCode = str;

	KFile file(LANGUAGES + str + L".txt");
	sf::String* segments;
	int length;

	for (bool b = true; b; )
	{
		file.readLine(segments, length);

		if (segments[0].toWideString().compare(L"single_player") == 0) { single_player = sf::String(segments[1]); }
		else if (segments[0].toWideString().compare(L"multi_player") == 0) { multi_player = sf::String(segments[1]); }
		else if (segments[0].toWideString().compare(L"settings") == 0) { settings = sf::String(segments[1]); }
		else if (segments[0].toWideString().compare(L"quit") == 0) { quit = sf::String(segments[1]); }
		else if (segments[0].toWideString().compare(L"loading") == 0) { loading = sf::String(segments[1]); }

		else if (segments[0].toWideString().compare(L"endFile") == 0)
		{
			b = false;
		}
	}
	file.close();
}

Language::Language()
{
	//This is in case that the language is not loaded
	langCode = L"en-US";
	
	single_player = L"Single Player";
	multi_player = L"Multi Player";
	settings = L"Settings";
	quit = L"Quit";
	loading = L"Loading...";
}