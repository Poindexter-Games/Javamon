#pragma once

#include <cstdint>
#include <SFML/Window/Keyboard.hpp>

#include <iostream>

#include "Variables.h"

class Controls
{
private:
	bool upPressed;
	bool upPressedLastTime;
	int  upPressedTime;
	sf::Keyboard::Key upKey;

	bool leftPressed;
	bool leftPressedLastTime;
	int  leftPressedTime;
	sf::Keyboard::Key leftKey;

	bool downPressed;
	bool downPressedLastTime;
	int  downPressedTime;
	sf::Keyboard::Key  downKey;

	bool rightPressed;
	bool rightPressedLastTime;
	int  rightPressedTime;
	sf::Keyboard::Key rightKey;

	bool selectPressed;
	bool selectPressedLastTime;
	int  selectPressedTime;
	sf::Keyboard::Key selectKey;

	bool cancelPressed;
	bool cancelPressedLastTime;
	int  cancelPressedTime;
	sf::Keyboard::Key cancelKey;

	bool rightClickPressed;
	bool rightClickPressedLastTime;
	int  rightClickPressedTime;

	bool leftClickPressed;
	bool leftClickPressedLastTime;
	int  leftClickPressedTime;

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
		if (selectPressed) selectPressedTime++;
		else selectPressedTime = 0;
		if (cancelPressed) cancelPressedTime++;
		else cancelPressedTime = 0;
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
		case SELECT:
			return selectPressed;
		case CANCEL:
			return cancelPressed;
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
		case SELECT:
			return selectPressedTime == 1;
		case CANCEL:
			return cancelPressedTime == 1;
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
	sf::Keyboard::Key getSelectKey() { return selectKey; }
	sf::Keyboard::Key getCancelKey() { return cancelKey; }

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
		case SELECT:
			selectPressed = pressed;
			break;
		case CANCEL:
			cancelPressed = pressed;
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
};