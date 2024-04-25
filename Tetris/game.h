#pragma once
#include "board.h"


class Game
{
	Board player1, player2;
	int status;

	void printTetris();

public:
	void printInstructions();
	int menu();
	void init();
	int run();
	void printMenu();
	int whereToMove(int keyPressed, int& direction);

};