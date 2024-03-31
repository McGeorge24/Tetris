#pragma once
#include "Grid.h"
#include "Block.h"

class Screen {
private:
	int width, height;

public:
	Screen(int screenwidth, int screenheight);

	bool ShouldClose();
	void LoadingScreen();
	void GameOverScreen();
	int Init(const char * title);
	void Update(Grid* grid, Block* block, Block * next, float* delta_time, int * score);

	~Screen();
};