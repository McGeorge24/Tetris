#include <raylib.h>
#include "Game.h"
#include <iostream>

Game::Game(int screenwidth, int screenheight) {
	width = screenwidth;
	height = screenheight;
}

int Game::Initscreen(const char* title) {
	InitWindow(width, height, title);
	cellsize = height / 20;
	SetTargetFPS(60);
	return 1;
}

bool Game::ShouldClose() {
	return WindowShouldClose();
}

void Game::LoadingScreen() {
	for (int i = 0; i < 256; i+=2) {
		BeginDrawing();
		ClearBackground(BLACK);
		DrawText("Tetris", width/2- cellsize - cellsize/2, height/2- (cellsize/5)*2, (cellsize/5)*4, {(unsigned char)i, (unsigned char)i, (unsigned char)i, (unsigned char)i});
		EndDrawing();
	}
}

void Game::GameOverScreen() {
	DrawRectangle(0, 0, width-6*cellsize, height, { 0, 0, 0, 192 });
	DrawRectangleGradientH(width-6*cellsize, 0, 6*cellsize, height, { 0,0,0,190 }, { 0,0,0,60 });
	DrawText("Game over", 2*cellsize, height / 2 - cellsize/2, cellsize, { 255, 0, 0, 192 });
}

void Game::Update(Grid * grid, Block * block, Block * next, Block * estimation, float delta_time, int time, int * score, int * level) {

	ClearBackground(BLACK);
	grid->Render(cellsize);	//render game grid
	DrawText("Tetris", 10 * cellsize + cellsize/5, cellsize/10, 2*cellsize-cellsize/5, WHITE);
	DrawRectangleGradientH(3*cellsize, 0, width-3*cellsize, height, { 100,0,235,0 }, { 100,0,235,145 });	//tetris color gradient over it
	
	//separating line
	DrawLine(10*cellsize, 0, 10*cellsize, height, { 160, 160, 180, 255 });
	//DrawLineEx({ 10.0*50+3, 0.0 }, { 10.0*50+3, 1.0f * height }, 5.0f, {160, 160, 180, 255});	//separating line (field/info)

	//next block display
	DrawRectangleRoundedLines({10.5f*cellsize, 2.0f*cellsize-cellsize/5.0f,  5.0f* cellsize, 3.5f* cellsize},0.1f, 8, cellsize/10.0f, WHITE);		//next -boundry
	DrawText("Next:", 11 * cellsize, 2 * cellsize+cellsize/10, (cellsize/5)*4, WHITE);	//next -text
	next->Render(cellsize);	//next -piece

	//level display
	DrawRectangleRoundedLines({ 10.5f * cellsize, 6.0f * cellsize - cellsize / 5.0f,  5.0f * cellsize, 1.5f * cellsize }, 0.1f, 8, cellsize / 10.0f, WHITE);	//score -boundry
	DrawText(TextFormat("Level %i", *level), 11 * cellsize, 6 * cellsize + cellsize / 10, (cellsize / 5) * 4, WHITE);	//score -points

	DrawRectangleRoundedLines({ 10.5f * cellsize, 11.0f * cellsize - cellsize / 5.0f,  5.0f * cellsize, 3.5f * cellsize }, 0.1f, 8, cellsize / 10.0f, WHITE);		//next -boundry
	DrawText("Hold:", 11 * cellsize, 11 * cellsize + cellsize / 10, (cellsize / 5) * 4, WHITE);	//next -text
	//render held piece

	if (grid->isGameOver()) {
		GameOverScreen();
		if (IsKeyPressed(KEY_ENTER)) {
			grid->Clear();
			delta_time = 0;
			*score = 0;
		}
	}
	else 
	{
		block->UpdatePositionPassive(delta_time);
		block->UpdatePosition(grid);
		estimation->HardDrop(grid);
		if (block->IsPlaced(grid)) {
			block->Join(grid);
			*block = *next;
			block->SetCoords(5, 1);
			next->Randomise((unsigned int)(time * 10000*width));
		}	
		
		estimation->Render(cellsize);
		block->Render(cellsize);
		*estimation = *block;
		estimation->ChangeColorBy(0, 0, 0, -175);
		grid->ClearLines(score);
	}
	
	//draw over potential game_over screen
	DrawRectangleRoundedLines({ 10.5f * cellsize, 8.0f*cellsize -cellsize/5.0f,  5.0f * cellsize, 2.5f * cellsize }, 0.1f, 8, cellsize/10.0f, WHITE);	//score -boundry
	DrawText("Score:", 11 * cellsize, 8 * cellsize + cellsize / 10, (cellsize / 5) * 4, WHITE);	//score -text
	DrawText(TextFormat("   %i", *score), 11 * cellsize, 9 * cellsize + cellsize / 10, (cellsize/5)*4, WHITE);	//score -points
}

void Game::Run() {

	Grid* grid = new Grid;
	Block* current_block = new Block(5, 1);
	Block* next_block = new Block(13, 5);
	Block* estimation = new Block(5, 1);
	//Block* on_hold = new Block(5, 5);

	Initscreen("Tetris");

	next_block->Randomise((int)this);
	current_block->Randomise((int)this);
	*estimation = *current_block;

	LoadingScreen();
	
	float delta_time = 0.0f;
	float time = 0.0f;
	int score = 0;
	int level = 1;
	while (!ShouldClose()) {

		BeginDrawing();
		Update(grid, current_block, next_block, estimation, delta_time, time, &score, &level);
		EndDrawing();
		delta_time = GetFrameTime();
		time += delta_time;
	}

	//delete on_hold;
	delete estimation;
	delete next_block;
	delete current_block;
	delete grid;
}

Game::~Game() {
	CloseWindow();
}