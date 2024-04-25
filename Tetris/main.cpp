

#include "game.h"
#include "gameLayout.h"
#include <iostream>
#include <time.h> 
using namespace std;

void main()
{
	srand(time(NULL));
	Game game;
	game.init();
	int temp = game.menu();
	if (temp == (int)GameLayout::eMenu::NEW_GAME)
	{
		int status = game.run();
		while (status == (int)GameLayout::eMenu::NEW_GAME)
		{
			game.init();
			status = game.run();
		}
	} 
	cout << endl << "Thank you for playing Tetris !" << endl;
}

