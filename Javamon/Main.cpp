#include "Main.h"

void render(sf::RenderWindow&);

int main()
{
	/*
	Sets the command prompt to display utf-8 text (use Lucida Console as your console font)
	The command prompt defaults to the ASCII encoding, but I wanted it temporarily changed to
	UTF-8 so at least I can see that the right number of letters are loaded from a language
	file even though Lucida Console can't display characters other than latin.
	*/
	_setmode(_fileno(stdout), _O_U8TEXT);

	/*
	The renderwindow needs to be instantiated in the main function for best initialization results.
	Also, I don't know how to properly code in C++, so it is going to stay here for now
	*/
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), WINDOW_TITLE);
	window.setFramerateLimit(FRAME_RATE_LIMIT); //Cap the framerate at 60fps
	window.setKeyRepeatEnabled(false);

	/*
	This is to instantiate a class called main which holds all of the available screens in the game
	*/
	Main main(window);

	/*
	Creates a thread for rendering the game
	*/
	sf::Thread render(&Main::render, &main);

	/*
	Starts the rendering thread and then proceeds to update the game
	*/
	render.launch();
	main.update();

	/*
	This is something I was told to include, maybe one day someone on our team will know what
	this is actually used for.
	*/
	render.wait();

	/*
	Clean up (nothing here)
	*/
	return 0;
}

Main::Main(sf::RenderWindow & window) : window(window)
{
	playingGame = true;
	
	/*
	Create the language variable (default: American English)
	*/
	l = Language("en-US");

	/*
	Load options from Options.txt
	Current things the program is looking for:
		openFile;
		language	=	[ja-JP]
	*/
	KFile options(sf::String(RESOURCES + "Options.txt"));
	wstring w;
	options.readLine(w);
	l = Language(StringEditor::substring(w, StringEditor::findCharacter(w, L'=', 1) + 1, w.length()));

	/*
	Instantiate the font based off of the game language
	English users don't need the Japanese character set loaded (saves space)
	*/
	font = KText(l);

	/*
	Sets the game state; the final version of the game should have this set to logo screen,
	then goes to the main menu
	*/
	gs = GameState::MAIN_MENU;

	/*
	Loads the game modes.
	Only one variable should be loaded at one point, so we need to figure out how to unload modes
	when you aren't using them. Ie, single player and multiplayer shouldn't be loaded on the stack
	(I don't think I am using that term correctly)
	*/
	mainMenu = MainMenu(l);

	/*
	Create a black background
	*/
	bg.setSize(sf::Vector2f((float)INT_MAX, (float)INT_MAX));
	bg.setFillColor(sf::Color::Black);
	bg.setPosition(sf::Vector2f((float)(INT_MIN / 2), (float)(INT_MIN / 2)));
}

void Main::update()
{
	sf::Clock clock;
	bool firstRun = true;
	while (playingGame)
	{
		if (firstRun || (float) clock.getElapsedTime().asMilliseconds() > FRAME_TIME)
		{
			eventHandler.eventListener(event, window, controls);

			//	Perform logic based upon events
			if (eventHandler.getWindowClosed())
			{
				playingGame = false;
			}

			controls.update(); //This calculates key press time


			if (gs == GameState::SINGLE_PLAYER)
			{
				sp.update(controls);
				if (sp.getRequestedMode() == Singleplayer::RequestMode::QUIT)
				{
					sp.setRequestedModeRead();
					gs = GameState::MAIN_MENU;
				}
			}
			else if (gs == GameState::MAIN_MENU)
			{
				mainMenu.update(controls);
				if (mainMenu.getRequestedMode() == MainMenu::RequestMode::SINGLE_PLAYER)
				{
					gs = GameState::LOADING;
					sp = Singleplayer(l, L"Poindexter", L"Test", L"TestLevel2");
					gs = GameState::SINGLE_PLAYER;
					mainMenu.setRequestedModeRead();
				}
				else if (mainMenu.getRequestedMode() == MainMenu::RequestMode::QUIT)
				{
					playingGame = false;
					mainMenu.setRequestedModeRead();
				}
			}

			clock.restart();
			firstRun = false;
		}
	}
}

void Main::render()
{
	sf::View view;
	view.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	view.setCenter(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	
	while (playingGame)
	{
		window.draw(bg);
		window.clear();
		window.setView(view);

		if (gs == GameState::SINGLE_PLAYER)
		{
			sf::RectangleShape a;
			a.setSize(sf::Vector2f((float)BLOCK_SIZE, (float)BLOCK_SIZE));
			a.setFillColor(sf::Color::Yellow);
			a.setPosition(sf::Vector2f(0.0f, 0.0f));

			sp.render(window, font);
		}
		else if (gs == GameState::MAIN_MENU)
		{
			mainMenu.render(window);
		}
		else if (gs == GameState::LOADING)
		{
			font.drawText(window, 0, 0, l.getLoading(), sf::Color::White);
		}

		window.display();
	}
}