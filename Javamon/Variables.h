#pragma once

#include <iostream>

const float SCREEN_HEIGHT = 720;
const float SCREEN_WIDTH = 1280;
const int FRAME_RATE_LIMIT = 60;
const std::wstring WINDOW_TITLE = L"ジャヴァモンスター";
const int BLOCK_SIZE = 64;
const int PLAYER_HEIGHT = (int)(BLOCK_SIZE * 1.25f);

enum Gender { MALE = 0, FEMALE = 1, NEUTER = 2 };
enum GameState { LEVEL = 0, LOADING = 1, BATTLE = 2 };
enum Direction { UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3 };
enum Control { C_UP = 0, C_LEFT = 1, C_DOWN = 2, C_RIGHT = 3, ACCEPT = 4, CANCEL = 5, START = 6, SELECT = 7, MOUSE_LEFT = 8, MOUSE_RIGHT = 9 };