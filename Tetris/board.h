#pragma once
#include "shape.h"
#include "gameLayout.h"

class Board
{
private:
	char board[GameLayout::GAME_HEIGHT][GameLayout::GAME_WIDTH];
	int counts[GameLayout::GAME_HEIGHT];
	int distance; // Distance from (0,0).
	Shape currShape;
	int score;
	void removeFullLines();

public:
	void init(int distance);
	void printFrame();
	void printBoard();
	bool isMoveOk(int direction);
	int run(int keyPressed);
	int getScore();

};

