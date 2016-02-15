#pragma once

#include <cstdint>
#include <SFML/Window/Keyboard.hpp>

#include <iostream>

#include "Variables.h"

class Controls
{
public:
	Controls();
	void update();
	bool isPressed(Control);

	bool isPressedForFirstTime(Control);

	bool isOnlyOneDirectionHeldDown();
	Direction getOnlyDirectionHeldDown();

	sf::Keyboard::Key getUpKey() { return upKey; }
	sf::Keyboard::Key getLeftKey() { return leftKey; }
	sf::Keyboard::Key getDownKey() { return downKey; }
	sf::Keyboard::Key getRightKey() { return rightKey; }
	sf::Keyboard::Key getAcceptKey() { return acceptKey; }
	sf::Keyboard::Key getCancelKey() { return cancelKey; }
	sf::Keyboard::Key getStartKey() { return startKey; }
	sf::Keyboard::Key getSelectKey() { return selectKey; }

	void setPressed(Control, bool);
	void setMousePos(int x, int y){
		mouseX = x;
		mouseY = y;
	}
	int getMouseX() { return mouseX; }
	int getMouseY() { return mouseY; }
	bool isPressed(Direction);
	int getTimePressed(Direction);

private:
	bool upPressed;
	unsigned int upPressedTime;
	sf::Keyboard::Key upKey;

	bool leftPressed;
	unsigned int leftPressedTime;
	sf::Keyboard::Key leftKey;

	bool downPressed;
	unsigned int downPressedTime;
	sf::Keyboard::Key downKey;

	bool rightPressed;
	unsigned int rightPressedTime;
	sf::Keyboard::Key rightKey;

	bool acceptPressed;
	unsigned int acceptPressedTime;
	sf::Keyboard::Key acceptKey;

	bool cancelPressed;
	unsigned int cancelPressedTime;
	sf::Keyboard::Key cancelKey;

	bool startPressed;
	unsigned int startPressedTime;
	sf::Keyboard::Key startKey;

	bool selectPressed;
	unsigned int selectPressedTime;
	sf::Keyboard::Key selectKey;

	bool rightClickPressed;
	unsigned int rightClickPressedTime;

	bool leftClickPressed;
	unsigned int leftClickPressedTime;

	int mouseX;
	int mouseY;
	int mouseXLastTime;
	int mouseYLastTime;
};