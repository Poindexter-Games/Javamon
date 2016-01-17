#pragma once
#ifndef _EVENTS_H_
#define _EVENTS_H_

#include <cstdint>
#include <string>

#include <SFML\Graphics.hpp>

class Level;

using namespace std;

class Events
{
public:
	void eventListener(sf::Event& event, sf::RenderWindow& window);
	bool getKeyPressed(std::string key);
	bool getMouseClicked(std::string button);
	bool getWindowClosed();
	void levelListener(string*, int);
	bool getLevelRequestChange(){return levelRequestsChange;}
	string getLevelName() { return newLevelName; }
private:
	// Booleans for key events
	bool aPressed = false, dPressed = false, wPressed = false, sPressed = false, shiftPressed = false, windowClosed = false;

	bool leftClick = false; //Left mouse button 

	int mouseX, mouseY;

	string newLevelName;
	bool levelRequestsChange = false;
};


#endif


