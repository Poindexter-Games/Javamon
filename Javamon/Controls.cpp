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