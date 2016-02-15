#include "Singleplayer.h"

Singleplayer::Singleplayer():Screen(Language())
{
	
}

Singleplayer::Singleplayer(Language lang, sf::String auth, sf::String pack, sf::String name):Screen(lang)
{
	l = Level(auth, pack, name, 0);
}

void Singleplayer::update(Controls & c)
{
	l.update(c, 0);

	if (l.isRequestingLevelChange())
	{
		Player p;
		sf::String s;

		l.getPlayer(p, s);
		l = Level(l.getAuth(), l.getPack(), s, p);
	}
}

void Singleplayer::render(sf::RenderWindow & w)
{
	if (l.getMode() == Level::Mode::REG)
	{
		l.render(w, 0);
	}
}
