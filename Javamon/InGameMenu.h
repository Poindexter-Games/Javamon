#pragma once

#include "Screen.h"

#include "Math.h"

#include "Controls.h"
#include "Variables.h"
#include "SFML/Graphics/RenderWindow.hpp"

#include "StringEditor.h"



class InGameMenu: public Screen
{
public:
	InGameMenu();
	void update(Controls&);
	void render(sf::RenderWindow&);
private:
	sf::Texture box;
	sf::Texture selector;
	int boxSelected;
};