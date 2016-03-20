#include "NPC.h"

NPC::NPC():MovableEntity(0, 0)
{
	Word w;
	w.langCode = L"code_CODE";
	w.str = L"Syôtaihumei";
	names.push_back(w);

	w.str = L"Dialoguehumei";
	dialogs.push_back(w);

	sex = Sex::MALE;

	dir = Direction::RIGHT;

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

void NPC::loadFromFile(KFile& file, sf::String auth, sf::String pack, sf::String name)
{
	sf::String* segments;
	int length;

	for (bool b = true; b; )
	{
		file.readLine(segments, length);
		if (length == 0) continue;

		if (length == 2)
		{
			if (StringEditor::equals(segments[0], L"name"))
			{
				Word w;
				w.langCode = L"code_CODE";
				w.str = segments[1];
				names[0] = w;
			}
			if (StringEditor::equals(segments[0], L"x"))
			{
				x = stoi(segments[1].toWideString());
				actualX = x * BLOCK_SIZE;
			}
			if (StringEditor::equals(segments[0], L"y"))
			{
				y = stoi(segments[1].toWideString());
				actualY = y * BLOCK_SIZE;
			}
			if (StringEditor::equals(segments[0], L"wantsToBattle"))
			{
				bool b = false;
				if (StringEditor::equals(segments[1], L"true"))
				{
					b = true;
				}
				wantsToBattle = b;
			}
			if (StringEditor::equals(segments[0], L"direction"))
			{
				int d = 3;
				if (StringEditor::equals(segments[1], L"UP"))
				{
					d = 0;
				}
				else if (StringEditor::equals(segments[1], L"LEFT"))
				{
					d = 1;
				}
				else if (StringEditor::equals(segments[1], L"DOWN"))
				{
					d = 2;
				}
				NPC::dir = to_Direction(d);
			}
			if (StringEditor::equals(segments[0], L"r"))
			{
				loadTextures(auth, pack, name, stoi(segments[1].toWideString()));
			}
			if (StringEditor::equals(segments[0], L"dialogue"))
			{
				Word w;
				w.langCode = L"code_CODE";
				w.str = segments[1];
				dialogs[0] = w;
			}
		}
		if (length == 3)
		{
			if (StringEditor::equals(segments[0], L"name"))
			{
				Word w;
				w.langCode = segments[1];
				w.str = segments[2];
				names.push_back(w);
			}
			if (StringEditor::equals(segments[0], L"dialogue"))
			{
				Word w;
				w.langCode = segments[1];
				w.str = segments[2];
				StringEditor::echo(segments[1]);
				dialogs.push_back(w);
			}
		
		}
		if (StringEditor::equals(segments[0], L"}"))
		{
			return;
		}
	}
}

sf::String NPC::getName(sf::String s)
{
	for (int i = 0; i < names.size(); i++)
	{
		if (StringEditor::equals(s, names[i].langCode))
		{
			return names[i].str;
		}
	}

	return dialogs[0].str;
}

sf::String NPC::getDialog(sf::String s)
{
	for (int i = 0; i < dialogs.size(); i++)
	{
		if (StringEditor::equals(s, dialogs[i].langCode))
		{
			return dialogs[i].str;
		}
	}

	return dialogs[0].str;
}

void NPC::render(sf::RenderWindow & w)
{
	sf::Sprite s(textures[(dir * 4)]);
	s.setPosition(sf::Vector2f(actualX, actualY - (PLAYER_HEIGHT - BLOCK_SIZE)));
	w.draw(s);
}