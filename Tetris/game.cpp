#include "game.h"
#include "gameLayout.h"
#include "general.h"
#include <iostream>
#include <Windows.h>
#include <conio.h> 

using namespace std;

void Game::init()
{
	// This function initiates the game struct.
	status = GameLayout::NO_GAME;
	player1.init(GameLayout::DISTANCE_PLAYER1);
	player2.init(GameLayout::DISTANCE_PLAYER2);
}

void Game::printInstructions()
{
	//This function prints the menu and keys of the game.
	clrscr();
	printTetris();
	cout << "The player must rotate, move, and drop the falling Tetriminos inside the Matrix (playing field)." << endl << "Lines are cleared when they are completely filled with Blocks and have no empty spaces." << endl;
	cout << "Keys:                   Left Player     Right Player" << endl;
	cout << "LEFT:                      a or A         j or J" << endl;
	cout << "RIGHT:                     d or D         l or L" << endl;
	cout << "ROTATE clockwise:          s or S         k or K" << endl;
	cout << "ROTATE counterclockwise:   w or W         i or I" << endl;
	cout << "DROP:                      x or X         m or M" << endl << endl;
	cout << "Score :" << endl << "FULL LINE : 100 points." << endl << endl;;
	cout << "Back To Menu, Press ESC";
	int keyPressed = 0;
	while (keyPressed != GameLayout::ESC)
	{
		if (_kbhit())
			keyPressed = _getch();
	}
}

int Game::run()
{
	// This function does the game. 
	// When the player loses or wants to start a new game, it comes back to main. 
	int status1 = 0, status2 = 0;
	int direction, player;
	status = GameLayout::IS_GAME;

	player1.printFrame();
	player2.printFrame();

	while (status1 != GameLayout::LOSER && status2 != GameLayout::LOSER)
	{
		int keyPressed = (int)GameLayout::eDirection::DOWN;
		if (_kbhit())
			keyPressed = _getch();
		if (keyPressed == GameLayout::ESC)
		{
			status = menu();
			if (status == (int)GameLayout::eMenu::NEW_GAME || status == (int)GameLayout::eMenu::EXIT)
				return status;
			if (status == (int)GameLayout::eMenu::RESUME_GAME)
			{
				player1.printBoard();
				player2.printBoard();
				status = GameLayout::IS_GAME;
			}
		}
		player = whereToMove(keyPressed, direction);
		if (player == GameLayout::PLAYER1)
		{
			status1 = player1.run(direction);
			status2 = player2.run((int)GameLayout::eDirection::DOWN);
		}
		else if (player == GameLayout::PLAYER2)
		{
			status1 = player1.run((int)GameLayout::eDirection::DOWN);
			status2 = player2.run(direction);
		}
		else
		{
			status1 = player1.run((int)GameLayout::eDirection::DOWN);
			status2 = player2.run((int)GameLayout::eDirection::DOWN);
		}
		Sleep(200);
	}
	clrscr();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	cout << "################################################################" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	cout << " ####    #    #   #  #####       ###    #   #  #####  #####     " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	cout << "#       # #   ## ##  #         #     #  #   #  #      #   #     " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	cout << "#  ##  #####  # # #  #####     #     #  #   #  #####  #####     " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	cout << "#   #  #   #  #   #  #         #     #  #   #  #      #  #      " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	cout << " ####  #   #  #   #  #####       ###      #    #####  #   #     " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
	cout << "################################################################" << endl << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),GameLayout::WHITE);

	if (status1 == GameLayout::LOSER)
		cout << "The winner is player 2 with " << player2.getScore() << " points !";
	else if (status2 == GameLayout::LOSER)
		cout << "The winner is player 1 with " << player1.getScore() << " points !";
	else if (player1.getScore() > player2.getScore())
		cout << "The winner is player 1 with " << player1.getScore() << " points !";
	else if (player2.getScore() > player1.getScore())
		cout << "The winner is player 2 with " << player2.getScore() << " points !";
	else 
		cout << "Draw with " <<player1.getScore() << " points !";
	return GameLayout::LOSER;

}

int Game::menu()
{
	// This functiom prints the menu of the game. 
	// It returns the number selected by the user.
	int option;
	printMenu();
	cin >> option;
	while (option == (int)GameLayout::eMenu::RESUME_GAME && status == -1)
	{
		cout << "Incorrect option, Try again.\n";
		cin >> option;
	}
	while (option != (int)GameLayout::eMenu::RESUME_GAME && option != (int)GameLayout::eMenu::INSTRUCTIONS &&
		option != (int)GameLayout::eMenu::NEW_GAME && option != (int)GameLayout::eMenu::EXIT )
	{
		cout << "Incorrect option, Try again.\n";
		cin >> option;
	}
	if (option == (int)GameLayout::eMenu::INSTRUCTIONS)
	{
		printInstructions();
		return menu();
	}
	clrscr();
	return option;
}

void Game::printMenu()
{
	// This function print the option to selcet.
	clrscr();
	printTetris();
	cout << "(1) Start a new game " << endl;
	if (status == GameLayout::IS_GAME)
		cout << "(2) Continue a paused game" << endl;
	cout << "(8) Present instructions and keys" << endl << "(9) EXIT " << endl;
}

int Game::whereToMove(int keyPressed, int& direction)
{
	// This function tells whwere the player wants to move.
	if (keyPressed == (int)GameLayout::eKey1::LEFT || keyPressed == ((int)toupper((char)GameLayout::eKey1::LEFT)))
	{
		direction = (int)GameLayout::eDirection::LEFT;
		return GameLayout::PLAYER1;
	}
	else if (keyPressed == (int)GameLayout::eKey2::LEFT || keyPressed == ((int)toupper((char)GameLayout::eKey2::LEFT)))
	{
		direction = (int)GameLayout::eDirection::LEFT;
		return GameLayout::PLAYER2;
	}
	else if (keyPressed == (int)GameLayout::eKey1::RIGHT || keyPressed == ((int)toupper((char)GameLayout::eKey1::RIGHT)))
	{
		direction = (int)GameLayout::eDirection::RIGHT;
		return GameLayout::PLAYER1;
	}
	else if (keyPressed == (int)GameLayout::eKey2::RIGHT || keyPressed == ((int)toupper((char)GameLayout::eKey2::RIGHT)))
	{
		direction = (int)GameLayout::eDirection::RIGHT;
		return GameLayout::PLAYER2;
	}
	else if (keyPressed == (int)GameLayout::eKey1::DROP || keyPressed == ((int)toupper((char)GameLayout::eKey1::DROP)))
	{
		direction = (int)GameLayout::eDirection::DROP;
		return GameLayout::PLAYER1;
	}
	else if (keyPressed == (int)GameLayout::eKey2::DROP || keyPressed == ((int)toupper((char)GameLayout::eKey2::DROP)))
	{
		direction = (int)GameLayout::eDirection::DROP;
		return GameLayout::PLAYER2;
	}
	else if (keyPressed == (int)GameLayout::eKey1::ROTATE_L || keyPressed == ((int)toupper((char)GameLayout::eKey1::ROTATE_L)))
	{
		direction = (int)GameLayout::eDirection::ROTATEL;
		return GameLayout::PLAYER1;
	}
	else if (keyPressed == (int)GameLayout::eKey2::ROTATE_L || keyPressed == ((int)toupper((char)GameLayout::eKey2::ROTATE_L)))
	{
		direction = (int)GameLayout::eDirection::ROTATEL;
		return GameLayout::PLAYER2;
	}
	else if (keyPressed == (int)GameLayout::eKey1::ROTATE_R || keyPressed == ((int)toupper((char)GameLayout::eKey1::ROTATE_R)))
	{
		direction = (int)GameLayout::eDirection::ROTATER;
		return GameLayout::PLAYER1;
	}
	else if (keyPressed == (int)GameLayout::eKey2::ROTATE_R || keyPressed == ((int)toupper((char)GameLayout::eKey2::ROTATE_R)))
	{
		direction = (int)GameLayout::eDirection::ROTATER;
		return GameLayout::PLAYER2;
	}
	else
	{
		direction = (int)GameLayout::eDirection::DOWN;
		return GameLayout::PLAYER1;
	}
}

void Game::printTetris()
{
	// This function print the tetris headLine.
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);

	cout << "#########################################" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);

	cout << "#####  #####  #####  #####  #####   #### " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);

	cout << "  #    #        #    #   #    #    #     " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);

	cout << "  #    #####    #    #####    #     ###  " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);

	cout << "  #    #        #    #  #     #        # " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),1);

	cout << "  #    #####    #    #   #  #####  ####  " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);

	cout << "#########################################" << endl << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),GameLayout ::WHITE);

}