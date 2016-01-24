#pragma once

#include <cstdint>
#include <SFML/Window/Keyboard.hpp>

#include <iostream>

#include "Variables.h"

class Controls
{
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
public:
	Controls();
	void update()
	{
		if (upPressed) upPressedTime++;
		else upPressedTime = 0;
		if (leftPressed) leftPressedTime++;
		else leftPressedTime = 0;
		if (downPressed) downPressedTime++;
		else downPressedTime = 0;
		if (rightPressed) rightPressedTime++;
		else rightPressedTime = 0;
		if (acceptPressed) acceptPressedTime++;
		else acceptPressedTime = 0;
		if (cancelPressed) cancelPressedTime++;
		else cancelPressedTime = 0;
		if (startPressed) startPressedTime++;
		else startPressedTime = 0;
		if (selectPressed) selectPressedTime++;
		else selectPressedTime = 0;
		if (leftClickPressed) leftPressedTime++;
		else leftClickPressedTime = 0;
		if (rightClickPressed) rightPressedTime++;
		else rightClickPressedTime = 0;

		mouseXLastTime = mouseX;
		mouseYLastTime = mouseY;
	}
	bool isPressed(Control c)
	{
		switch(c)
		{
		case C_UP:
			return upPressed;
		case C_LEFT:
			return leftPressed;
		case C_DOWN:
			return downPressed;
		case C_RIGHT:
			return rightPressed;
		case ACCEPT:
			return acceptPressed;
		case CANCEL:
			return cancelPressed;
		case START:
			return startPressed;
		case SELECT:
			return selectPressed;
		case MOUSE_LEFT:
			return leftClickPressed;
		case MOUSE_RIGHT:
			return rightClickPressed;
		}
	}

	bool isPressedForFirstTime(Control c)
	{
		switch (c)
		{
		case C_UP:
			return upPressedTime == 1;
		case C_LEFT:
			return leftPressedTime == 1;
		case C_DOWN:
			return downPressedTime == 1;
		case C_RIGHT:
			return rightPressedTime == 1;
		case ACCEPT:
			return acceptPressedTime == 1;
		case CANCEL:
			return cancelPressedTime == 1;
		case START:
			return startPressedTime == 1;
		case SELECT:
			return selectPressedTime == 1;
		case MOUSE_LEFT:
			return leftClickPressedTime == 1;
		case MOUSE_RIGHT:
			return rightClickPressedTime == 1;
		}
	}

	sf::Keyboard::Key getUpKey() { return upKey; }
	sf::Keyboard::Key getLeftKey() { return leftKey; }
	sf::Keyboard::Key getDownKey() { return downKey; }
	sf::Keyboard::Key getRightKey() { return rightKey; }
	sf::Keyboard::Key getAcceptKey() { return acceptKey; }
	sf::Keyboard::Key getCancelKey() { return cancelKey; }
	sf::Keyboard::Key getStartKey() { return startKey; }
	sf::Keyboard::Key getSelectKey() { return selectKey; }

	void setPressed(Control c, bool pressed)
	{
		switch (c)
		{
		case C_UP:
			upPressed = pressed;
			break;
		case C_LEFT:
			leftPressed = pressed;
			break;
		case C_DOWN:
			downPressed = pressed;
			break;
		case C_RIGHT:
			rightPressed = pressed;
			break;
		case ACCEPT:
			acceptPressed = pressed;
			break;
		case CANCEL:
			cancelPressed = pressed;
		case START:
			startPressed = pressed;
			break;
		case SELECT:
			selectPressed = pressed;
			break;
		case MOUSE_LEFT:
			leftClickPressed = pressed;
			break;
		case MOUSE_RIGHT:
			rightClickPressed = pressed;
			break;
		}
	}
	void setMousePos(int x, int y)
	{
		mouseX = x;
		mouseY = y;
	}
	int getMouseX() { return mouseX; }
	int getMouseY() { return mouseY; }
	bool isPressed(Direction d)
	{
		if (d == Direction::UP && upPressed == true)
			return true;
		if (d == Direction::LEFT && leftPressed == true)
			return true;
		if (d == Direction::DOWN && downPressed == true)
			return true;
		if (d == Direction::RIGHT && rightPressed == true)
			return true;
		return false;
	}
	int getTimePressed(Direction d)
	{
		if (d == Direction::UP)
			return upPressedTime;
		if (d == Direction::LEFT)
			return leftPressedTime;
		if (d == Direction::DOWN)
			return downPressedTime;
		if (d == Direction::RIGHT)
			return rightPressedTime;
		return 0;
	}
};