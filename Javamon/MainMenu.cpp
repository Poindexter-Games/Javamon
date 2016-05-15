#include "MainMenu.h"

MainMenu::MainMenu()
{
	//DO NOT FORGET TO RUN THE LANGUAGE CONSTRUCTOR
}

MainMenu::MainMenu(Language l)
{
	//Set the request mode to none
	m = RequestMode::NONE;
	//Set the selected box to -1 (no box selected)
	boxSelected = -1;

	//Initialize the Title splash
	logoTexture = sf::Texture();

	if (StringEditor::equals(l.getLanguageCode(), L"ja-JP"))
	{
		//Load the Japanese Title Splash
		logoTexture.loadFromFile(VIDEO + "TitleJP.png");
	}
	else
	{
		//Load the English Title Splash (or any other languages' splash)
		logoTexture.loadFromFile(VIDEO + "Title.png");
	}

	//Initialize the standard bar texture
	standardBar = sf::Texture();
	//Initialize the selected bar texture
	selectedBar = sf::Texture();
	//Initialize the greyed select bar texture
	loadingBar = sf::Texture();

	//Load the standard bar texture
	standardBar.loadFromFile(VIDEO + L"Bar.png",sf::IntRect(0, 40, 640, 40));
	//Load the selected bar texture
	selectedBar.loadFromFile(VIDEO + L"Bar.png",sf::IntRect(0, 00, 640, 40));
	//Load the greyed select bar texture
	loadingBar.loadFromFile(VIDEO + L"Bar.png",	sf::IntRect(0, 80, 640, 40));
}

void MainMenu::update(Controls & c)
{
	//Check what box the player has cursor in
	bool inABox = false;
	for (int i = 0; i < 4; i++)
	{
		if (contains(c.getMouseX(), c.getMouseY(), sf::IntRect(320, 400 + (i * 80), 640, 40)))
		{
			inABox = true;
			boxSelected = i;
		}
	}
	//If not in a box, then unselect any boxes
	if (!inABox)
	{
		boxSelected = -1;
	}

	if (boxSelected == 0)
	{
		if (c.isPressedForFirstTime(Control::MOUSE_LEFT))
		{
			//If single player mode is selected, go to single player mode
			m = RequestMode::SINGLE_PLAYER;
		}
	}
	else if (boxSelected == 1)
	{
		if (c.isPressedForFirstTime(Control::MOUSE_LEFT))
		{
			//If multi-player mode is selected, go to multi-player mode
			m = RequestMode::MULTI_PLAYER;
		}
	}
	else if (boxSelected == 2)
	{
		if (c.isPressedForFirstTime(Control::MOUSE_LEFT))
		{
			//If options is selected, go to the options
			m = RequestMode::OPTIONS;
		}
	}
	else if (boxSelected == 3)
	{
		if (c.isPressedForFirstTime(Control::MOUSE_LEFT))
		{
			//If quit is selected, quit
			m = RequestMode::QUIT;
		}
	}
}

void MainMenu::render(sf::RenderWindow & w, Language & l, KText & f)
{
	//DRAW LOGO
	sf::Sprite s;
	s.setPosition(sf::Vector2f(320, 45));
	s.setTexture(logoTexture);
	w.draw(s);

	//DRAW BOXES
	for (int i = 0; i < 4; i++)
	{
		s.setPosition(sf::Vector2f(320, 400 + (i * 80)));
		if (i == boxSelected)
		{
			s.setTexture(selectedBar);
		}
		else
		{
			s.setTexture(standardBar);
		}
		w.draw(s);
	}

	//Draw Text for single-player mode
	f.drawText(w, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 + 40, l.getSinglePlayer(), sf::Color::White);
	//Draw text for multi-player mode
	f.drawText(w, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 + 120, l.getMultiPlayer(), sf::Color::White);
	//Draw text for settings
	f.drawText(w, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 + 200, l.getSettings(), sf::Color::White);
	//Draw text for quit
	f.drawText(w, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 + 280, l.getQuit(), sf::Color::White);
}