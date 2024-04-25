#include "shape.h"
#include <stdlib.h>
#include <Windows.h>
#include <iostream>


void Shape::init(int distance)
{
	// This function rand a number betaween 0-6 and initiate the shape by its.
	shapeType = rand() % GameLayout::NUM_OF_SHAPES;
	color = GameLayout::arrShapeColors[shapeType];
	switch (shapeType) // The middle is 6.
	{
	case (int)GameLayout::eShapes::SQUARE: 
	{
		body[0].init(5 + distance, 1);
		body[1].init(5 + distance, 2);
		body[2].init(6 + distance, 1);
		body[3].init(6 + distance, 2);
		break;
	}
	case (int)GameLayout::eShapes::LINE: 
	{
		body[0].init(4 + distance, 1);
		body[1].init(5 + distance, 1);
		body[2].init(6 + distance, 1);
		body[3].init(7 + distance, 1);
		break;
	}
	case (int)GameLayout::eShapes::T:
	{
		body[0].init(4 + distance, 1);
		body[1].init(5 + distance, 1);
		body[2].init(5 + distance, 2);
		body[3].init(6 + distance, 1);
		break;
	}
	case (int)GameLayout::eShapes::L:
	{
		body[0].init(5 + distance, 1);
		body[1].init(5 + distance, 2);
		body[2].init(5 + distance, 3);
		body[3].init(6 + distance, 3);
		break;
	}
	case (int)GameLayout::eShapes::REVERSED_L:
	{
		body[0].init(6 + distance, 1);
		body[1].init(6 + distance, 2);
		body[2].init(6 + distance, 3);
		body[3].init(5 + distance, 3);
		break;
	}
	case (int)GameLayout::eShapes::Z:
	{
		body[0].init(4 + distance, 1);
		body[1].init(5 + distance, 1);
		body[2].init(5 + distance, 2);
		body[3].init(6 + distance, 2);
		break;
	}
	case (int)GameLayout::eShapes::REVERSED_Z:
	{
		body[0].init(4 + distance, 2);
		body[1].init(5 + distance, 2);
		body[2].init(5 + distance, 1);
		body[3].init(6 + distance, 1);
		break;
	}
	}
}

void Shape::draw()
{
	// This function draw the shape.
	for (int i = 0; i < GameLayout::NUM_OF_BODY; i++)
		body[i].draw('*',color);
}

void Shape::remove()
{
	// This function remove the shape from the board.
	for (int i = 0; i < GameLayout::NUM_OF_BODY; i++)
		body[i].draw(' ',GameLayout::BLACK);
}

void Shape::set(int direction)
{
	// This function set the body to the next place.
	for (int i = 0; i < GameLayout::NUM_OF_BODY; i++)
	{
		if (direction == (int)GameLayout::eDirection::LEFT)
			body[i].move(-1, 0);
		else if (direction == (int)GameLayout::eDirection::DOWN)
			body[i].move(0, 1);
		else if (direction == (int)GameLayout::eDirection::RIGHT)
			body[i].move(1, 0);
	}
}

bool Shape::isMoveOk(const char(&board)[GameLayout::GAME_HEIGHT][GameLayout::GAME_WIDTH], int &direction, int distance)
{
	// This function cheak if the move is ok.
	int x, y;
	for (int i = 0; i < GameLayout::NUM_OF_BODY; i++) 
	{
		x = body[i].getX();
		y = body[i].getY();
		if (y >= GameLayout::GAME_HEIGHT)
			return false;
		else if (direction == (int)GameLayout::eDirection::LEFT && x == distance)
			direction = (int)GameLayout::eDirection::DOWN;
		else if (direction == (int)GameLayout::eDirection::RIGHT && x == distance + GameLayout::GAME_WIDTH - 1)
			direction = (int)GameLayout::eDirection::DOWN;
		if (board[y][x - distance + direction] != ' ')
			return false;
	}
	return true;
}

void Shape::updateBoard(char (&board)[GameLayout::GAME_HEIGHT][GameLayout::GAME_WIDTH],int (&count)[GameLayout::GAME_HEIGHT], int distance)
{
	// This function update the board using this shape.
	int x, y;
	for (int i = 0; i < GameLayout::NUM_OF_BODY; i++)
	{
		x = body[i].getX();
		y = body[i].getY();
		board[y-1][x - distance] = GameLayout::arrColors[shapeType];
		count[y-1]++;
	}
}

bool Shape::isInsideBoard(int distance)
{
	// This function cheak if the shape is inside the board.
	int x;
	for (int i = 0; i < GameLayout::NUM_OF_BODY; i++)
	{
		x = body[i].getX();
		if (x < distance || x > distance + GameLayout::GAME_WIDTH - 1)
			return false;
	}
	return true;
}

void Shape::rotate(const char(&board)[GameLayout::GAME_HEIGHT][GameLayout::GAME_WIDTH], int &direction, int distance)
{
	// This function rotates the shape.
	if (shapeType == (int)GameLayout::eShapes::SQUARE)
		return;
	Point temp[GameLayout::NUM_OF_BODY];
	for (int i = 0; i < GameLayout::NUM_OF_BODY; i++)
	{
		int relativeX = body[i].getX() - body[1].getX(); 
		int relativeY = body[i].getY() - body[1].getY(); 
		if (direction == (int)GameLayout::eDirection::ROTATER)
			temp[i].init(body[1].getX() + relativeY, body[1].getY() - relativeX);
		else // counterclockwise
			temp[i].init(body[1].getX() - relativeY, body[1].getY() + relativeX);
	}

	if (isRotateOk(board, temp, distance))
	{
		remove();
		for (int i = 0; i < GameLayout::NUM_OF_BODY; i++)
			body[i].init(temp[i].getX(), temp[i].getY());
	}
	else
		direction = (int)GameLayout::eDirection::DOWN;

}

bool Shape::isRotateOk(const char(&board)[GameLayout::GAME_HEIGHT][GameLayout::GAME_WIDTH], Point(&temp)[GameLayout::NUM_OF_BODY], int distance)
{
	// This function cheak if rotate is ok, if not it's cheak if it can move left/ right to rotate.
	int x, y;
	for (int i = 0; i < GameLayout::NUM_OF_BODY; i++)
	{
		x = temp[i].getX();
		y = temp[i].getY();
		if (board[y][x - 1] != ' ')
			return false;
		else if (x <= distance - 1)
		{
			for (int j = 0; j < GameLayout::NUM_OF_BODY; j++)
				temp[j].move(1,0);
			i= -1;
		}
		else if(x >= distance + GameLayout::GAME_WIDTH - 1)
		{
			for (int j = 0; j < GameLayout::NUM_OF_BODY; j++)
				temp[j].move(-1,0);
			i = -1;
		}
		else if (y >= GameLayout::GAME_HEIGHT)
			return false;
	}
	return true;
}