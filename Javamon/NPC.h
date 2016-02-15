#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/String.hpp>

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <vector>

#include "Variables.h"
#include "StringEditor.h"

#include "MovableEntity.h"

class NPC:public MovableEntity
{
public:
	NPC();
	void render(sf::RenderWindow&);
	void loadTextures(sf::String, sf::String, sf::String, int);
protected:
private:
	sf::String name;
	Gender sex;
	Direction d;
	std::vector<sf::Texture> textures;
	bool battler;
	bool wantsToBattle;
};