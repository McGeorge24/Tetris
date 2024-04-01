#include <raylib.h>
#include "Game.h"
#include <iostream>

Game::Game(int screenwidth, int screenheight) {
	width = screenwidth;
	height = screenheight;
}

int Game::Initscreen(const char* title) {
	InitWindow(width, height, title);
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
		DrawText("Tetris", width/2-85, 480, 40, {(unsigned char)i, (unsigned char)i, (unsigned char)i, (unsigned char)i});
		EndDrawing();
	}
}

void Game::GameOverScreen() {
	DrawRectangle(0, 0, width-300, height, { 0, 0, 0, 192 });
	DrawRectangleGradientH(width-300, 0, 300, height, { 0,0,0,190 }, { 0,0,0,60 });
	DrawText("Game over", 115, height / 2 - 25, 50, { 255, 0, 0, 192 });
}

void Game::Update(Grid * grid, Block * block, Block * next, Block * estimation, float delta_time, int time, int * score) {

	ClearBackground(BLACK);
	grid->Render(50);	//render game grid
	DrawText("Tetris", 10 * 50 + 9, 5, 90, WHITE);
	DrawRectangleGradientH(150, 0, width-150, height, { 100,0,235,0 }, { 100,0,235,145 });	//tetris color gradient over it
	DrawLineEx({ 10.0*50+3, 0.0 }, { 10.0*50+3, 1.0f * height }, 5.0f, {160, 160, 180, 255});	//separating line (field/info)
	DrawRectangleRoundedLines({10.5*50, 1.0*90,  5.0* 50, 3.5* 50},0.1f, 8, 5.0f, WHITE);		//next -boundry
	DrawText("Next:", 11 * 50, 2 * 50+5, 40, WHITE);	//next -text
	next->Render(50);	//next -piece

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
		
		estimation->Render(50);
		block->Render(50);
		*estimation = *block;
		estimation->ChangeColorBy(0, 0, 0, -175);
		grid->ClearLines(score);
	}
	
	//draw over potential game_over screen
	DrawRectangleRoundedLines({ 10.5 * 50, 1.0 * 290,  5.0 * 50, 2.5 * 50 }, 0.1f, 8, 5.0f, WHITE);	//score -boundry
	DrawText("Score:", 11 * 50, 6 * 50 + 5, 40, WHITE);	//score -text
	DrawText(TextFormat("   %i", *score), 11 * 50, 7 * 50 + 5, 40, WHITE);	//score -points
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
	while (!ShouldClose()) {

		BeginDrawing();
		Update(grid, current_block, next_block, estimation, delta_time, time, &score);
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