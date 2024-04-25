#pragma once
#include "point.h"
#include "gameLayout.h"

class Shape
{
private:
	Point body[GameLayout::NUM_OF_BODY];
	int shapeType;
	int color;
	bool isRotateOk(const char(&board)[GameLayout::GAME_HEIGHT][GameLayout::GAME_WIDTH], Point(&temp)[GameLayout::NUM_OF_BODY], int distance);

public:
	void init(int distance);
	void set(int direction);
	void draw();
	void remove();
	bool isMoveOk(const char (& board)[GameLayout::GAME_HEIGHT][GameLayout::GAME_WIDTH], int &direction, int distance);
	void updateBoard(char (&board)[GameLayout::GAME_HEIGHT][GameLayout::GAME_WIDTH], int(&count)[GameLayout::GAME_HEIGHT], int distance);
	bool isInsideBoard(int distance);
	void rotate(const char(&board)[GameLayout::GAME_HEIGHT][GameLayout::GAME_WIDTH], int &direction, int distance);

};
