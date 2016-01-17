#include "Events.h"

using namespace std;

void Events::eventListener(sf::Event& event, sf::RenderWindow& window)
{
	//	Look for events and deal with them
	while (window.pollEvent(event))  //pollEvent function checks whether any events have occured, if so will return true until all events have been dealt with
	{

		//	If window is closed, end game loop.
		if (event.type == sf::Event::Closed)
		{
			windowClosed = true;
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

		if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::LShift || event.key.code == sf::Keyboard::RShift))
		{
			shiftPressed = true;
		}

		if (event.type == sf::Event::KeyReleased && (event.key.code == sf::Keyboard::LShift || event.key.code == sf::Keyboard::RShift))
		{
			shiftPressed = false;
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
}

bool Events::getKeyPressed(std::string key)
{
	if ((key == "A" || key == "a") && aPressed)
	{
		return true;
	}
	else if ((key == "W" || key == "w") && wPressed)
	{
		return true;
	}
	else if ((key == "D" || key == "d") && dPressed)
	{
		return true;
	}
	else if ((key == "S" || key == "s") && sPressed)
	{
		return true;
	}
	else if ((key == "LShift" || key == "RShift") && shiftPressed)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Events::getMouseClicked(std::string button)
{
	if ((button == "L" || button == "l") && leftClick)
	{
		leftClick = false;
		return true;
	}
	else
	{
		return false;
	}
}

bool Events::getWindowClosed()
{
	if (windowClosed)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
Gathers all of the data from the level to sort into requests
x 
levelChange,name,2 - Level is requesting change of levels
x
Author: Karl Piepho
Date Created: 1/16/2016
*/
void Events::levelListener(string* events, int length)
{
	if (length == 2 && events[0] == "levelChange")
	{
		levelRequestsChange = true;
		newLevelName = events[1];
	}
}

