#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>

#include "Variables.h"
#include "Controls.h"
#include "KText.h"

using namespace std;

class Screen
{
public:
	Screen();
	void update(Controls);
	void render(sf::RenderWindow &);

protected:
	enum Mode { REG = 0, LOADING = 1 };
	Mode m;
	Controls c;
private:
};