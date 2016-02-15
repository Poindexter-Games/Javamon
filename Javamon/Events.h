#pragma once
#ifndef _EVENTS_H_
#define _EVENTS_H_

#include <cstdint>
#include <string>
#include <iostream>

#include <SFML\Graphics.hpp>

#include "Controls.h"
#include "Level.h"
#include "Battle.h"

using namespace std;

class Events
{
public:
	void eventListener(sf::Event& event, sf::RenderWindow& window, Controls&);
	bool getWindowClosed();
private:
	// Booleans for key events
	bool windowClosed = false;
};
#endif


