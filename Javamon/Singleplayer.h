#pragma once

#include <SFML/System/String.hpp>

#include "Screen.h"
#include "Battle.h"

#include "Controls.h"
#include "Language.h"
#include "Level.h"

class Singleplayer: public Screen
{
public:
	enum RequestMode{QUIT, NONE};
	RequestMode getRequestedMode() { return rm; }
	void setRequestedModeRead() { rm = RequestMode::NONE; }

	Singleplayer();
	Singleplayer(Language, sf::String, sf::String, sf::String);
	void update(Controls &);
	void render(sf::RenderWindow &, KText &);
	enum Mode{ LEVEL = 0, BATTLE = 1 };
protected:
private:
	RequestMode rm;
	Mode mode;
	Level l;
	Battle b;
};