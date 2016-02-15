#include "Singleplayer.h"

Singleplayer::Singleplayer():Screen(Language())
{
	
}

Singleplayer::Singleplayer(Language lang, sf::String auth, sf::String pack, sf::String name):Screen(lang)
{
	//load from save file
	m = Mode::LOADING;
	
	l = Level(auth, pack, name, 0);

	m = Mode::REG;
}

void Singleplayer::update(Controls & c)
{
	l.update(c, 0);

	if (l.isRequestingLevelChange())
	{
		m = Mode::LOADING;
		Player p;
		sf::String s;

		l.getPlayer(p, s);

		l = Level(l.getAuth(), l.getPack(), s, p);

		m = Mode::REG;
	}
}

void Singleplayer::render(sf::RenderWindow & w)
{
	if (m == Mode::REG)
	{
		l.render(w, 0);
	}
}
