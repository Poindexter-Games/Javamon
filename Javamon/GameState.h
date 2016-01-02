#pragma once
#include <SFML/Graphics.hpp>

#include "Level.h"
#include <string>
#include <cstdint>

using namespace std;

class GameState
{
private:
	string state;
	Level l;
public:
	GameState(string);
	void update();
	void render(sf::RenderWindow& window);
};