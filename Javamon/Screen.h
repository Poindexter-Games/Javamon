#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>

#include "Variables.h"
#include "Controls.h"
#include "KText.h"

/*
A class that holds two methods specifically for overriding.

Author: Karl
*/
class Screen
{
public:
	/*
	Instantiates the window
	*/
	Screen();
	/*
	Updates the window
	*/
	void update(Controls);
	/*
	Draws the window
	*/
	void render(sf::RenderWindow &);
protected:
	/*
	Holds a protected mode variable that shows what state the window is in.
	*/
	enum Mode { REG = 0, LOADING = 1 };
	Mode m;
	
	/*
	Allows the render method to access the input from the last update.
	*/
	Controls c;
private:
};