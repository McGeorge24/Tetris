#pragma once
#include "Grid.h"
#include "Block.h"

class Game {
private:
	int width, height;

public:
	Game(int screenwidth, int screenheight);

	void Run();
	bool ShouldClose();
	void LoadingScreen();
	void GameOverScreen();
	int Initscreen(const char * title);
	void Update(Grid* grid, Block* block, Block * next, Block * estimation, float delta_time, int time, int * score);

	~Game();
};