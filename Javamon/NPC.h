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

#include "KFile.h"

class NPC:public MovableEntity
{
public:
	NPC();

	void render(sf::RenderWindow&);
	void loadTextures(sf::String, sf::String, sf::String, int);

	void loadFromFile(KFile&, sf::String, sf::String, sf::String);

	sf::String getName(sf::String);
	sf::String getDialog(sf::String);
protected:
private:
	std::vector<Word> names;
	Sex sex;
	Direction dir;
	std::vector<sf::Texture> textures;
	std::vector<Word> dialogs;
	bool battler;
	bool wantsToBattle;
};