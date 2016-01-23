#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Player.h"

class Battle
{
private:
	sf::RectangleShape bg;
public:
	Battle();
	void render(sf::RenderWindow&);
	void update(bool* digitalControls);
};