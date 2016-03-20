#pragma once

#include <SFML/System/String.hpp>
#include <iostream>

const float SCREEN_HEIGHT = 720;
const float SCREEN_WIDTH = 1280;
const int FRAME_RATE_LIMIT = 60;
const float FRAME_TIME = 1000 / FRAME_RATE_LIMIT;
const sf::String WINDOW_TITLE = L"Javamon";
const int BLOCK_SIZE = 64;
const int PLAYER_HEIGHT = (int)(BLOCK_SIZE * 1.25f);
const int DIALOG_BOX_HEIGHT = 200;
const int DIALOG_BOX_LOW = SCREEN_HEIGHT - DIALOG_BOX_HEIGHT;

const int FONT_SIZE = 32;

const sf::String RESOURCES = L"Resources/";
const sf::String VIDEO = RESOURCES + L"Video/";
const sf::String PACKS = RESOURCES + L"Packs/";
const sf::String SAVES = RESOURCES + L"Saves/";
const sf::String LANGUAGES = RESOURCES + L"Languages/";

enum Sex { MALE = 0, FEMALE = 1};
enum GameState { MAIN_MENU = 0, LOADING = 1, SINGLE_PLAYER = 2};
enum Direction { UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3 };
enum Control { C_UP = 0, C_LEFT = 1, C_DOWN = 2, C_RIGHT = 3, ACCEPT = 4, CANCEL = 5, START = 6, SELECT = 7, MOUSE_LEFT = 8, MOUSE_RIGHT = 9 };

static Direction to_Direction(int i)
{
	if (i == 0) return UP;
	if (i == 1) return LEFT;
	if (i == 2) return DOWN;
	return RIGHT;
}

struct Word
{
	sf::String langCode;
	sf::String str;
};

struct Variable
{
	sf::String identifier;
	int value;
};