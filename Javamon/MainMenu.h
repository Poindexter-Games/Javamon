#pragma once

#include "Screen.h"

#include <SFML\Graphics\Texture.hpp>

#include "Variables.h"
#include "StringEditor.h"
#include "Language.h"
#include "KText.h"
#include "Math.h"

class MainMenu : public Screen
{
public:
	/*
	An enumerated list that tells the parent class what GameState the main requests a chage to.

	Author: Karl Piepho
	Date Revised: April 29, 2016
	Revised By: Karl Piepho
	*/
	enum RequestMode { SINGLE_PLAYER, MULTI_PLAYER, OPTIONS, QUIT, NONE };

	/*
	A default constructior for the main menu.
	Make sure you run the MainMenu(Language) constructor!

	Author: Karl Piepho
	Date Revised: April 29, 2016
	Revised By: Karl Piepho
	*/
	MainMenu();
	/*
	The actual constructor for the main menu.
	Loads the images for the main menu and changes the bars depended on the user's language.

	Author: Karl Piepho
	Date Revised: April 29, 2016
	Revised By: Karl Piepho
	*/
	MainMenu(Language);
	/*
	This updates the menu depended on the player's control input.

	Author: Karl Piepho
	Date Revised: April 29, 2016
	Revised By: Karl Piepho
	*/
	void update(Controls & c);
	/*
	This renders the game to the RenderWindow using the user's language
	with the help of the Text drawing functions provided by KText.

	Author: Karl Piepho
	Date Revised: April 29, 2016
	Revised By: Karl Piepho
	*/
	void render(sf::RenderWindow&, Language&, KText&);

	/*
	A public method to let the owner (superclass) of MainMenu know what mode the
	player wants to change to.

	Author: Karl Piepho
	Date Revised: April 29, 2016
	Revised By: Karl Piepho
	*/
	RequestMode getRequestedMode() const { return m; }
	/*
	A method that resets the player selected mode to RequestMode::NONE.
	This method may be overriden with a deconstructor later if I can figure out how to use them.

	Author: Karl Piepho
	Date Revised: April 29, 2016
	Revised By: Karl Piepho
	*/
	void setRequestedModeRead() { m = RequestMode::NONE; }
private:
	/*
	This is the box selected on the main menu.
	-1 for no boxes selected.
	0 for single-player.
	1 for multi-player.
	2 for settings.
	3 for quit.

	Author: Karl Piepho
	Date Revised: April 29, 2016
	Revised By: Karl Piepho
	*/
	int boxSelected = 0;

	/*
	Holds the mode that the player wants to go to.

	Author: Karl Piepho
	Date Revised: April 29, 2016
	Revised By: Karl Piepho
	*/
	RequestMode m;

	/*
	This is the game's logo.
	The current textures for this are Title.png and TitleJP.png (<-- for the Japanese version)

	Author: Karl Piepho
	Date Revised: April 29, 2016
	Revised By: Karl Piepho
	*/
	sf::Texture logoTexture;
	/*
	This an unselected bar.

	Author: Karl Piepho
	Date Revised: April 29, 2016
	Revised By: Karl Piepho
	*/
	sf::Texture standardBar;
	/*
	This a bar that is selected.

	Author: Karl Piepho
	Date Revised: April 29, 2016
	Revised By: Karl Piepho
	*/
	sf::Texture selectedBar;
	/*
	This was the bar that was selected and now is greyed out as the level loads.
	Not implemented.

	Author: Karl Piepho
	Date Revised: April 29, 2016
	Revised By: Karl Piepho
	*/
	sf::Texture loadingBar;
};