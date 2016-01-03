#include "Main.h"

int main()
{

	//	Asset Creation/Window Settings
	const float SCREEN_HEIGHT = 720;
	const float SCREEN_WIDTH = 1280;
	const int FRAME_RATE_LIMIT = 60;
	const std::string WINDOW_TITLE = "Javamon";

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Javamon");
	window.setFramerateLimit(FRAME_RATE_LIMIT); //Cap the framerate at 60fps
	window.setKeyRepeatEnabled(false);
	

	sf::Event event; //Object for handling/storing events
	Events eventHandler;

	Level level;

	bool playingGame = true; //Keeps the game running while true
	
	sf::View view;
	view.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	view.setCenter(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));

	//sf::RectangleShape bg;
	//bg.setSize(sf::Vector2f(1280, 720));
	//bg.setFillColor(sf::Color::Green);
	//bg.setPosition(sf::Vector2f(0, 0));


	sf::RectangleShape bg;
	bg.setSize(sf::Vector2f(INT_MAX, INT_MAX));
	bg.setFillColor(sf::Color::Black);
	bg.setPosition(sf::Vector2f(INT_MIN / 2, INT_MIN / 2));

	sf::RectangleShape test;
	test.setSize(sf::Vector2f(64, 64));
	test.setFillColor(sf::Color::Yellow);
	test.setPosition(sf::Vector2f(0, 0));

	bool c_up, c_left, c_down, c_right = false;
	
	// Game loop
	while (playingGame)
	{
		//Listen for events
		eventHandler.eventListener(event, window);

		//	Perform logic based upon events
		if (eventHandler.getWindowClosed())
		{
			playingGame = false;
		}

		if (eventHandler.getKeyPressed("W"))
		{
			c_up = true;

			std::cout << "Player pressed up\n";
		}

		if (eventHandler.getKeyPressed("A"))
		{
			c_left = true;

			std::cout << "Player pressed left\n";
		}

		if (eventHandler.getKeyPressed("S"))
		{
			c_down = true;

			std::cout << "Player pressed down\n";
		}

		if (eventHandler.getKeyPressed("D"))
		{
			c_right = true;

			std::cout << "Player pressed right\n";
		}

		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::W)){c_up    = false;}
		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::A)){c_left  = false;}
		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::S)){c_down  = false;}
		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::D)){c_right = false;}

		bool digitalControls[4] = {c_up, c_left, c_down, c_right};
		level.update(digitalControls);

		//	Render graphical changes
		window.clear();
		window.setView(view);
		window.draw(bg);
		level.render(window);
		//window.draw(test);

		window.display();

		

	}


	//	Cleanup / Exit Game
	window.close();

	return 0;
}