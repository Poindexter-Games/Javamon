#include "Main.h"

void render(sf::RenderWindow&);

int main()
{
	//Sets the command prompt to display utf-8 text (use Lucida Console as your font)
	_setmode(_fileno(stdout), _O_U8TEXT);

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), WINDOW_TITLE);
	window.setFramerateLimit(FRAME_RATE_LIMIT); //Cap the framerate at 60fps
	window.setKeyRepeatEnabled(false);

	Main main(window);

	//sf::Thread update(&Main::update, &main);
	sf::Thread render(&Main::render, &main);

	//update.launch();
	render.launch();
	main.update();

	//update.wait();
	render.wait();

	return 0;
}

Main::Main(sf::RenderWindow & window) : window(window)
{

	playingGame = true;
	
	//en_US
	//ja_JP
	Language lang = Language("en_US");

	gs = GameState::SINGLE_PLAYER;

	mainMenu = MainMenu(lang);
	sp = Singleplayer(lang, L"Poindexter", L"Test", L"TestLevel");

	bg.setSize(sf::Vector2f((float)INT_MAX, (float)INT_MAX));
	bg.setFillColor(sf::Color::Black);
	bg.setPosition(sf::Vector2f((float)(INT_MIN / 2), (float)(INT_MIN / 2)));

	delta = 0;
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
			}
			if (gs == GameState::MAIN_MENU)
			{
				mainMenu.update(controls);
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

			sp.render(window);
		}
		if (gs == GameState::MAIN_MENU)
		{
			mainMenu.render(window);
		}

		window.display();
	}
}