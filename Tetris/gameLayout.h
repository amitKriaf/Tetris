#pragma once
#include <Windows.h>

class GameLayout
{

public:
	enum class eKey1 { LEFT = 'a', RIGHT = 'd', ROTATE_R = 's', ROTATE_L = 'w', DROP = 'x' };
	enum class eKey2 { LEFT = 'j', RIGHT = 'l', ROTATE_R = 'k', ROTATE_L = 'i', DROP = 'm' };
	enum class eDirection { LEFT = -1, DOWN = 0, RIGHT = 1, DROP = 2, ROTATEL = 3, ROTATER = 4 };
	enum class eShapes {SQUARE = 0, LINE = 1, T = 2, L = 3, REVERSED_L = 4, Z = 5, REVERSED_Z = 6};
	enum class eMenu { NEW_GAME = 1, RESUME_GAME = 2, INSTRUCTIONS = 8, EXIT = 9 };
	static constexpr char arrColors[7] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g' };
	static constexpr int arrShapeColors[7] = { 14, 11, 5, 6, 1, 4, 10};
	static constexpr int NUM_OF_COLORS = 7;
	static constexpr int WHITE = 15;
	static constexpr int BLACK = 0;
	static constexpr int ESC = 27;
	static constexpr int DISTANCE_PLAYER1 = 1;
	static constexpr int DISTANCE_PLAYER2 = 23;
	static constexpr int GAME_WIDTH = 12;
	static constexpr int GAME_HEIGHT = 18;
	static constexpr int NUM_OF_BODY = 4;
	static constexpr int NUM_OF_SHAPES = 7;
	static constexpr int LOSER = -1;
	static constexpr int IS_GAME= 1;
	static constexpr int NO_GAME = -1;
	static constexpr int PLAYER1 = 1;
	static constexpr int PLAYER2 = 2;
	static constexpr int SCORE = 100;

};
