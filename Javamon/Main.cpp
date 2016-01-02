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

	GameState gs("level");

	bool playingGame = true; //Keeps the game running while true
	
	sf::View view;
	view.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	view.setCenter(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));

	

	sf::CircleShape player(32);
	player.setFillColor(sf::Color::White);
	player.setPosition(SCREEN_WIDTH / 2 - player.getRadius(), SCREEN_HEIGHT / 2 - player.getRadius());

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

		if (eventHandler.getKeyPressed("A"))
		{
			player.move(-5, 0);
			view.move(-5, 0);

			std::cout << "Player has moved to the left\n";

		}

		if (eventHandler.getKeyPressed("D"))
		{

			player.move(5, 0);
			view.move(5, 0);

			std::cout << "Player has moved to the right\n";

		}

		if (eventHandler.getKeyPressed("S"))
		{

			player.move(0, 5);
			view.move(0, 5);


			std::cout << "Player has moved downwards\n";

		}

		if (eventHandler.getKeyPressed("W"))
		{

			player.move(0, -5);
			view.move(0, -5);

			std::cout << "Player has moved upwards\n";

		}

		if (eventHandler.getMouseClicked("L"))
		{
			if (player.getFillColor() == sf::Color::White)
			{
				player.setFillColor(sf::Color::Blue);
			}
			else
			{
				player.setFillColor(sf::Color::White);
			}

			std::cout << "Player has changed color!\n";
		}

		//	Render graphical changes
		window.clear();
		window.setView(view);
		window.draw(bg);
		gs.render(window);
		//window.draw(test);
		
		window.draw(player);

		window.display();

		

	}


	//	Cleanup / Exit Game
	window.close();

	return 0;
}