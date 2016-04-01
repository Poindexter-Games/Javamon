#include "Singleplayer.h"

Singleplayer::Singleplayer()
{
	rm = RequestMode::NONE;
}

Singleplayer::Singleplayer(Language lang, sf::String auth, sf::String pack, sf::String name)
{
	rm = RequestMode::NONE;

	mode = Mode::LEVEL;
	l = Level(auth, pack, name, 0);
	l.setLanguageOfPlayer(0, lang);
}

void Singleplayer::update(Controls & c)
{
	if (mode == Mode::LEVEL)
	{
		l.update(c, 0);

		if (l.isRequestingLevelChange())
		{
			Player p;
			sf::String s;

			l.getPlayer(p, s);
			l = Level(l.getAuth(), l.getPack(), s, p);
		}
		if (l.getRequestedMode() == Level::RequestMode::MAIN_MENU)
		{
			l.setRequestedModeRead();
			rm = RequestMode::QUIT;
		}
	}
	else if (mode == Mode::BATTLE)
	{
		
	}
}

void Singleplayer::render(sf::RenderWindow & w, KText & font)
{
	if (mode == Mode::LEVEL)
	{
		if (l.getMode() == Level::Mode::REG)
		{
			l.render(w, font, 0);
		}
	}
	else if (mode == Mode::BATTLE)
	{
	
	}
}