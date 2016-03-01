#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Controls.h"
#include "Player.h"

class Battle
{
private:
	unsigned int numFrames;
	bool running;
	sf::RectangleShape bg;
public:
	Battle();
	void render(sf::RenderWindow&, int);
	void update(Controls&, int);
	bool isOver() { return !running; }
};