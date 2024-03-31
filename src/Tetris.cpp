// Tetris.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "Screen.h"


int main()
{
	Screen* screen = new Screen(800, 1000);
	Grid* grid = new Grid;
	std::cout << grid->grid << std::endl;
	Block* current_block = new Block(5, 1);
	Block* next_block = new Block(13, 5);
	screen->Init("Tetris");

	next_block->Randomise((int)screen);
	current_block->Randomise((int)screen);
	screen->LoadingScreen();
	float delta_time = 0.0f;
	int score = 0;
	while (!screen->ShouldClose()) {
		BeginDrawing();
		screen->Update(grid, current_block, next_block, &delta_time, &score);
		EndDrawing();
		delta_time += GetFrameTime();
	}

	delete next_block;
	delete current_block;
	delete grid;
	delete screen;
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
