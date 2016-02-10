#include "Screen.h"

Screen::Screen(Language l)
{
	Screen::l = l;
}

void Screen::setLanguage(Language l)
{
	Screen::l = l;
}

void Screen::update(Controls c)
{
	Screen::c = c;
}

void Screen::render(sf::RenderWindow & w, KText kt)
{
	sf::RectangleShape r(sf::Vector2f(SCREEN_WIDTH, SCREEN_WIDTH));
	r.setPosition(sf::Vector2f(0, 0));
	r.setFillColor(sf::Color::Black);

	sf::View view;
	view.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	view.setCenter(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	w.setView(view);
	
	w.draw(r);
	//kt.simpleMessage(w, L"ロード中…");
	kt.simpleMessage(w, l.getLoading().toWideString());
}