#pragma once

#include "Screen.h"

#include "SFML/Graphics/RenderWindow.hpp"



class InGameMenu: public Screen
{
public:
	InGameMenu();
	void render(sf::RenderWindow&);
};