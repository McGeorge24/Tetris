// Tetris.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "Game.h"


int main()
{	
	int screenheight;
	std::cout << "Enter screen height (must be a multiple of 200)" << std::endl;
	std::cin >> screenheight;
	Game * game = new Game((screenheight / 20) * 16, screenheight);
	game->Init("Tetris");
	game->Run();
	delete game;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
