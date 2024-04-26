#pragma once
#include "Grid.h"
#include "Block.h"

class Game {
private:

	// constants
	int width, height;
	int cellsize;
	Image window_icon;

	//game state
	int level;
	int score;
	int lines_cleared;
	float last_update_time = 0;
	
	//entities
	Grid grid;
	Block* current_block;
	Block* next_block; 
	Block* estimation;
	Block* on_hold;

	bool EventTriggered(float interval);
	void HandleInput();

public:
	Game(int screenwidth, int screenheight);

	void Run();
	bool ShouldClose();
	void LoadingScreen();
	void GameOverScreen();
	int Init(const char * title);
	void Render();

	~Game();
};