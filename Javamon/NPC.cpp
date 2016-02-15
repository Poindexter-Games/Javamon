#include "NPC.h"

NPC::NPC():MovableEntity(0, 0)
{
	name = "Syôtaihumei";
	sex = Gender::MALE;

	d = Direction::RIGHT;

	battler = false;
	wantsToBattle = false;
}

void NPC::loadTextures(sf::String auth, sf::String pack, sf::String name, int n)
{
	sf::Image textureSheet;
	textureSheet.loadFromFile(PACKS + auth + L"/" + pack + L"/" + name + "/NPCs.png");

	textures.resize(16);
	for (int i = 0; i < 16; i++)
	{
		textures[i].loadFromImage(textureSheet, sf::IntRect(i * BLOCK_SIZE, PLAYER_HEIGHT * n, BLOCK_SIZE, PLAYER_HEIGHT));
	}
}

void NPC::render(sf::RenderWindow & w)
{
	sf::Sprite s(textures[(d * 4)]);
	s.setPosition(sf::Vector2f(actualX, actualY - (PLAYER_HEIGHT - BLOCK_SIZE)));
	w.draw(s);
}


