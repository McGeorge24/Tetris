#pragma once
#include "Grid.h"
#include "Block.h"

class Game {
private:

	// constants
	int width, height;
	int cellsize;
	Image window_icon;
	Music normal_theme;
	Music intense_theme;
	Texture2D settings;
	float texture_scale;

	//game state
	int state;
	//0 = play
	//1 = game over
	//2 = info (i)
	//3 = settings & controls (?)
	//4 = paused

	//stats
	int level;
	int score;
	float last_update_time;
	float update_interval;
	
	//entities
	Grid grid;
	Block* current_block;
	Block* next_block; 
	Block* estimation;
	Block* on_hold;

	bool EventTriggered(float interval);
	void HandleInput();
	void Update();
	
	//mouse position
	bool IsMouseInCell(int x, int y);

public:
	//clear lines needs access to thiss
	int lines_cleared;

	Game(int screenwidth, int screenheight);

	void Run();
	bool ShouldClose();
	void LoadingScreen();
	void GameOverScreen();
	void PlayScreen();
	void InfoScreen();
	void SettingsScreen();

	int Init(const char * title);
	void Render();

	void Cleanup();
	~Game();
};