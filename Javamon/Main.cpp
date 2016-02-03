#include "Main.h"

int main()
{
	Language lang = Language::EN_US;
	//Test

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), WINDOW_TITLE);
	window.setFramerateLimit(FRAME_RATE_LIMIT); //Cap the framerate at 60fps
	window.setKeyRepeatEnabled(false);
	
	Controls controls;
	KText font(lang);

	sf::Event event; //Object for handling/storing events
	Events eventHandler;

	GameState gs = GameState::LEVEL;

	//Level level(0, -1, -1, -1);
	Level level(lang, L"Poindexter", L"Test", L"TestLevel");

	Battle battle;

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

	sf::RectangleShape test;
	test.setSize(sf::Vector2f(64, 64));
	test.setFillColor(sf::Color::Yellow);
	test.setPosition(sf::Vector2f(0, 0));
	
	// Game loop
	while (playingGame)
	{
		//Listen for events
		eventHandler.eventListener(event, window, controls);

		if(level.isRequestingLevelChange())
		{
			gs = GameState::LOADING;
			wstring auth = level.getAuth().toWideString();
			wstring pack = level.getPack().toWideString();
			wstring name = level.getToLevelName().toWideString();
			wcout << auth << L" " << pack << L" " << name << endl;
			int x = level.getToLevelX();
			int y = level.getToLevelY();
			int d = level.getToLevelDirection();
			level = Level(lang, auth, pack, name, level.getToLevelX(), level.getToLevelY(), level.getToLevelDirection());
			gs = GameState::LEVEL;
		}
		if (level.isRequestingBattleScreen())
		{
			gs = GameState::BATTLE;
		}
		if (battle.isOver())
		{
			gs == GameState::LEVEL;
		}

		//	Perform logic based upon events
		if (eventHandler.getWindowClosed())
		{
			playingGame = false;
		}
		
		controls.update(); //This calculates key press time

		if (gs == GameState::LEVEL)
		{
			level.update(controls);
		}

		//	Render graphical changes
		window.clear();
		window.setView(view);
		window.draw(bg);
		if (gs == GameState::LEVEL)
		{
			level.render(window, font);
		}
		if (gs == GameState::BATTLE)
		{
			battle.render(window);
		}
		window.display();

		

	}
	//	Cleanup / Exit Game
	window.close();


	return 0;
}