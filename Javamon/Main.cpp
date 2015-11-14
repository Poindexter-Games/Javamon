//	Libraries
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

int main()
{

	//	Asset Creation/Window Settings
	sf::RenderWindow window(sf::VideoMode(800, 600), "Game");
	window.setFramerateLimit(60); //Cap the framerate at 60fps
	window.setKeyRepeatEnabled(false);

	sf::Event event; //Object for handling/storing events

	bool playingGame = true; //Keeps the game running while true

	int mouseX, mouseY;

	sf::CircleShape player(50);
	player.setFillColor(sf::Color::White);
	player.setPosition(10, 10);


	sf::RectangleShape bg;
	bg.setSize(sf::Vector2f(800, 600));
	bg.setFillColor(sf::Color::Green);


	// Booleans for key events
	bool aPressed = false, dPressed = false, wPressed = false, sPressed = false;

	bool leftClick = false; //Left mouse button 
							// Game loop
	while (playingGame)
	{
		//	Look for events and deal with them
		while (window.pollEvent(event))  //pollEvent function checks whether any events have occured, if so will return true until all events have been dealt with
		{

			//	If window is closed, end game loop.
			if (event.type == sf::Event::Closed)
			{
				playingGame = false;
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
			{
				aPressed = true;
			}

			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::A)
			{
				aPressed = false;
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
			{
				dPressed = true;
			}

			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::D)
			{
				dPressed = false;
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
			{
				sPressed = true;
			}

			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::S)
			{
				sPressed = false;
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W)
			{
				wPressed = true;
			}

			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::W)
			{
				wPressed = false;
			}

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				leftClick = true;
			}

			if (event.type == sf::Event::MouseMoved)
			{
				mouseX = event.mouseMove.x;
				mouseY = event.mouseMove.y;
			}

		}

		//	Perform logic based upon events
		if (aPressed)
		{
			player.move(-10, 0);

			std::cout << "Player has moved to the left\n";

		}

		if (dPressed)
		{
			player.move(10, 0);
			std::cout << "Player has moved to the right\n";

		}

		if (sPressed)
		{
			player.move(0, 10);
			std::cout << "Player has moved downwards\n";

		}

		if (wPressed)
		{
			player.move(0, -10);
			std::cout << "Player has moved upwards\n";

		}

		if (leftClick)
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
			leftClick = false;
		}


		//	Render graphical changes
		window.clear();
		window.draw(bg);
		window.draw(player);

		window.display();

	}


	//	Cleanup / Exit Game
	window.close();

	return 0;
}
