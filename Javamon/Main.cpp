#include "Main.h"

void render(sf::RenderWindow&);

int main()
{
	//Sets the command prompt to display utf-8 text (use Lucida Console as your font)
	_setmode(_fileno(stdout), _O_U8TEXT);
	//The string should be set to "en_US"
	Language lang = Language("en_US");

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), WINDOW_TITLE);
	window.setFramerateLimit(FRAME_RATE_LIMIT); //Cap the framerate at 60fps
	window.setKeyRepeatEnabled(false);
	
	Controls controls;
	KText font(lang);

	sf::Event event; //Object for handling/storing events
	Events eventHandler;

	GameState gs = GameState::SINGLE_PLAYER;

	MainMenu mainMenu(lang);
	Singleplayer singleplayer(lang, L"Poindexter", L"Test", L"TestLevel");

	bool playingGame = true; //Keeps the game running while true
	
	sf::View view;
	view.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	view.setCenter(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));

	//sf::RectangleShape bg;
	//bg.setSize(sf::Vector2f(1280, 720));
	//bg.setFillColor(sf::Color::Green);
	//bg.setPosition(sf::Vector2f(0, 0));


	sf::RectangleShape bg;
	bg.setSize(sf::Vector2f((float)INT_MAX, (float)INT_MAX));
	bg.setFillColor(sf::Color::Black);
	bg.setPosition(sf::Vector2f((float)(INT_MIN / 2), (float)(INT_MIN / 2)));
	
	// Game loop
	while (playingGame)
	{
		//Listen for events
		eventHandler.eventListener(event, window, controls);

		//	Perform logic based upon events
		if (eventHandler.getWindowClosed())
		{
			playingGame = false;
		}
		
		controls.update(); //This calculates key press time
		
		
		if (gs == GameState::SINGLE_PLAYER)
		{
			singleplayer.update(controls);
		}
		if (gs == GameState::MAIN_MENU)
		{
			mainMenu.update(controls);
		}

		//	Render graphical changes
		window.clear();
		window.setView(view);
		window.draw(bg);

		if (gs == GameState::SINGLE_PLAYER)
		{
			singleplayer.render(window);
		}
		if (gs == GameState::MAIN_MENU)
		{
			mainMenu.render(window);
		}

		window.display();

		

	}
	//	Cleanup / Exit Game
	window.close();


	return 0;
}