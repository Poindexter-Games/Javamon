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

	selectPressed = false;
	selectPressedTime = 0;
	selectKey = sf::Keyboard::L;

	cancelPressed = false;
	cancelPressedTime = 0;
	cancelKey = sf::Keyboard::J;

	leftClickPressed = false;
	leftClickPressedTime = 0;

	rightClickPressed = false;
	rightClickPressedTime = 0;

	int mouseX = 0;
	int mouseY = 0;
	int mouseXLastTime = 0;
	int mouseYLastTime = 0;
	}