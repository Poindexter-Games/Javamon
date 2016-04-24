#include "Language.h"

Language::Language(sf::String str)
{
	langCode = str;

	KFile file(LANGUAGES + str + L".txt");
	wstring w;

	for (bool b = true; b; )
	{
		file.readLine(w);

		if (w.length() == 0) continue;

		if (StringEditor::equals(w, L"endFile;"))
		{
			break;
		}

		int comma = StringEditor::findCharacter(w, L'=', 1);
		wstring tag = StringEditor::substring(w, 0, comma);
		wstring text = StringEditor::substring(w, comma + 1, w.length());

		StringEditor::equals(tag, L"");

		if (StringEditor::equals(tag, L"single_player"))		{ single_player = text; }
		else if (StringEditor::equals(tag, L"multi_player"))	{ multi_player = text; }
		else if (StringEditor::equals(tag, L"settings"))		{ settings = sf::String(text); }
		else if (StringEditor::equals(tag, L"quit"))			{ quit = sf::String(text); }
		else if (StringEditor::equals(tag, L"loading"))			{ loading = sf::String(text); }
		else if (StringEditor::equals(tag, L"trainer"))			{ trainer = sf::String(text); }
		else if (StringEditor::equals(tag, L"main_menu"))		{ main_menu = sf::String(text); }
		else if (StringEditor::equals(tag, L"bag"))				{ bag = sf::String(text); }
		else if (StringEditor::equals(tag, L"monster"))			{ monster = sf::String(text); }
		else if (StringEditor::equals(tag, L"map"))				{ map = sf::String(text); }
		else if (StringEditor::equals(tag, L"phone"))			{ phone = sf::String(text); }
		else if (StringEditor::equals(tag, L"save"))			{ save = sf::String(text); }
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
	trainer = L"Trainer";
	main_menu = L"Main Menu";
	bag = L"Bag";
	monster = L"Monsters";
	map = L"Map";
	phone = L"Phone";
	save = L"Save";
}