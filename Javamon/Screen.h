#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Variables.h"
#include "Controls.h"
#include "Language.h"
#include "KText.h"

class Screen
{
protected:
	Language l;
	Controls c;
public:
	Screen(Language);
	void setLanguage(Language);
	void update(Controls);
	void render(sf::RenderWindow &, KText kt);
private:
};