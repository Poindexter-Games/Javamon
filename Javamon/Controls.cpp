#include "Controls.h"

Controls::Controls()
{
	upPressed = false;
	upPressedTime = 0;
	upKey = sf::Keyboard::W;

	leftPressed = false;
	leftPressedTime = 0;
	leftKey = sf::Keyboard::A;

	downPressed = false;
	downPressedTime = 0;
	downKey = sf::Keyboard::S;

	rightPressed = false;
	rightPressedTime = 0;
	rightKey = sf::Keyboard::D;

	acceptPressed = false;
	acceptPressedTime = 0;
	acceptKey = sf::Keyboard::Numpad6;

	cancelPressed = false;
	cancelPressedTime = 0;
	cancelKey = sf::Keyboard::Numpad4;

	startPressed = false;
	startPressedTime = 0;
	startKey = sf::Keyboard::Numpad3;

	selectPressed = false;
	selectPressedTime = 0;
	selectKey = sf::Keyboard::Numpad1;

	leftClickPressed = false;
	leftClickPressedTime = 0;

	rightClickPressed = false;
	rightClickPressedTime = 0;

	int mouseX = 0;
	int mouseY = 0;
	int mouseXLastTime = 0;
	int mouseYLastTime = 0;
}

void Controls::update()
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

bool Controls::isPressed(Control c)
{
	switch (c)
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

bool Controls::isPressedForFirstTime(Control c)
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

bool Controls::isOnlyOneDirectionHeldDown()
{
	if (upPressed && !leftPressed && !downPressed && !rightPressed)
		return true;
	else if (!upPressed && leftPressed && !downPressed && !rightPressed)
		return true;
	else if (!upPressed && !leftPressed && downPressed && !rightPressed)
		return true;
	else if (!upPressed && !leftPressed && !downPressed && rightPressed)
		return true;
	else return false;
}

Direction Controls::getOnlyDirectionHeldDown()
{
	if (upPressed) return UP;
	if (leftPressed) return LEFT;
	if (downPressed) return DOWN;
	return RIGHT;
}

void Controls::setPressed(Control c, bool pressed)
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

bool Controls::isPressed(Direction d)
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

int Controls::getTimePressed(Direction d)
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
