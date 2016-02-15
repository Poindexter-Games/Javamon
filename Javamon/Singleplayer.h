#pragma once

#include <SFML/System/String.hpp>

#include "Screen.h"

#include "Controls.h"
#include "Language.h"
#include "Level.h"

class Singleplayer: public Screen
{
public:
	Singleplayer(Language, sf::String, sf::String, sf::String);
	void update(Controls &);
	void render(sf::RenderWindow & w);
protected:
private:
	Level l;
};