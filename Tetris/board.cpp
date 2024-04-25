#include "board.h"
#include "general.h"
#include "gameLayout.h"
#include <iostream>
#include <Windows.h>
#include <conio.h> 
using namespace std;

void Board::init(int distance)
{
	// This function initiate the board struct.
	this->distance = distance;
	score = 0;
	for (int i = 0; i < GameLayout::GAME_HEIGHT; i++)
	{
		counts[i] = 0;
		for (int j = 0; j < GameLayout::GAME_WIDTH; j++)
			board[i][j] = ' ';
	}
	currShape.init(distance);
}

void Board::printFrame()
{
	// This function is printing the borders of a player.
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameLayout::WHITE);
	for (int col = 0; col <= GameLayout::GAME_WIDTH; col++)
	{
		gotoxy(col + distance - 1, 0);
		cout << "-";

		gotoxy(col + distance - 1, GameLayout::GAME_HEIGHT + 1);
		cout << "-";

	}

	for (int row = 0; row <= GameLayout::GAME_HEIGHT + 1; row++)
	{
		gotoxy(distance - 1, row);
		cout << "|";

		gotoxy(distance + GameLayout::GAME_WIDTH, row);
		cout << "|";

	}
	gotoxy(distance, GameLayout::GAME_HEIGHT + 3);
	cout << "Score: " << score;
}

void Board::printBoard()
{
	// This function print the board of the game.
	printFrame();
	for (int i = 0; i < GameLayout::GAME_HEIGHT; i++)
	{
		gotoxy(distance, i + 1);
		for (int j = 0; j < GameLayout::GAME_WIDTH; j++)
		{
			if (board[i][j] != ' ')
			{ 
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),GameLayout::arrShapeColors[board[i][j] - 'a']);
				cout << '*';
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameLayout::BLACK);
				cout << ' ';
			}
		}
			
	}

}

void Board::removeFullLines()
{
	// This function romove all the full lines.
	for (int i = GameLayout::GAME_HEIGHT - 1; i >= 0; i--)
		if (counts[i] == GameLayout::GAME_WIDTH)
		{
			score += GameLayout::SCORE;
			for (int j = i; j >= 1; j--)
			{
				for (int k = 0; k < GameLayout::GAME_WIDTH; k++)
				{
					board[j][k] = ' ';
					board[j][k] = board[j - 1][k];
				}
				counts[j] = counts[j - 1];
			}
			counts[0] = 0;
			i++; // In case of more than one line to Remove.
		}
	printBoard();
}

bool Board::isMoveOk(int direction)
{
	// This function checks if a certion move is ok.
	if (currShape.isMoveOk(board, direction, distance))
	{
		currShape.remove();
		Sleep(100);
		currShape.set(direction);
		currShape.draw();
		return true;
	}
	return false;
}

int Board::getScore()
{
	// This function return the score of the player.
	return score;
}

int Board::run(int keyPressed)
{
	// This function checks the move selected by the user. 
	// Then it updates the board, if the game ended, it returns a messege.

	int status = 0;
	int direction = keyPressed;
	currShape.draw();

	if (!currShape.isInsideBoard(distance))
		direction = (int)GameLayout::eDirection::DOWN;

	if (direction == (int)GameLayout::eDirection::ROTATER || direction == (int)GameLayout::eDirection::ROTATEL)
	{
		currShape.rotate(board, direction, distance);
		direction = (int)GameLayout::eDirection::DOWN;
	}

	else if (direction == (int)GameLayout::eDirection::DROP)
	{
		isMoveOk((int)GameLayout::eDirection::DOWN);
		direction = (int)GameLayout::eDirection::DOWN;
		Sleep(50);
	}
	else if (direction == (int)GameLayout::eDirection::LEFT || direction == (int)GameLayout::eDirection::RIGHT) // To go down between two key preesed. 
	{
		isMoveOk(direction);
		direction = (int)GameLayout::eDirection::DOWN;
	}
	if (!isMoveOk(direction))
	{
		currShape.updateBoard(board, counts, distance);
		removeFullLines();
		currShape.init(distance);
	}
	if (board[0][GameLayout::GAME_WIDTH / 2] != ' ')
		status = GameLayout::LOSER;

	return status;
}