#include "Events.h"

using namespace std;

void Events::eventListener(sf::Event& event, sf::RenderWindow& window, Controls& c)
{
	//	Look for events and deal with them
	while (window.pollEvent(event))  //pollEvent function checks whether any events have occured, if so will return true until all events have been dealt with
	{

		//	If window is closed, end game loop.
		if (event.type == sf::Event::Closed)
		{
			windowClosed = true;
		}

		if(event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == c.getUpKey())
			{
				c.setPressed(Control::C_UP, true);
			}
			if (event.key.code == c.getLeftKey())
			{
				c.setPressed(Control::C_LEFT, true);
			}
			if (event.key.code == c.getDownKey())
			{
				c.setPressed(Control::C_DOWN, true);
			}
			if (event.key.code == c.getRightKey())
			{
				c.setPressed(Control::C_RIGHT, true);
			}
			if (event.key.code == c.getAcceptKey())
			{
				c.setPressed(Control::ACCEPT, true);
			}
			if (event.key.code == c.getCancelKey())
			{
				c.setPressed(Control::CANCEL, true);
			}
			if (event.key.code == c.getStartKey())
			{
				c.setPressed(Control::START, true);
			}
			if (event.key.code == c.getSelectKey())
			{
				c.setPressed(Control::SELECT, true);
			}
		}
		else if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				c.setPressed(Control::MOUSE_LEFT, true);
			}
			else if(event.mouseButton.button == sf::Mouse::Right)
			{
				c.setPressed(Control::MOUSE_RIGHT, true);
			}
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == c.getUpKey())
			{
				c.setPressed(Control::C_UP, false);
			}
			if (event.key.code == c.getLeftKey())
			{
				c.setPressed(Control::C_LEFT, false);
			}
			if (event.key.code == c.getDownKey())
			{
				c.setPressed(Control::C_DOWN, false);
			}
			if (event.key.code == c.getRightKey())
			{
				c.setPressed(Control::C_RIGHT, false);
			}
			if (event.key.code == c.getAcceptKey())
			{
				c.setPressed(Control::ACCEPT, false);
			}
			if (event.key.code == c.getCancelKey())
			{
				c.setPressed(Control::CANCEL, false);
			}
			if (event.key.code == c.getStartKey())
			{
				c.setPressed(Control::START, false);
			}
			if (event.key.code == c.getSelectKey())
			{
				c.setPressed(Control::SELECT, false);
			}
		}
		else if (event.type == sf::Event::MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				c.setPressed(Control::MOUSE_LEFT, false);
			}
			else if (event.mouseButton.button == sf::Mouse::Right)
			{
				c.setPressed(Control::MOUSE_RIGHT, false);
			}
		}

		if (event.type == sf::Event::MouseMoved)
		{
			c.setMousePos(event.mouseMove.x * SCREEN_WIDTH / window.getSize().x, event.mouseMove.y * SCREEN_HEIGHT / window.getSize().y);
		}
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