#include <raylib.h>
#include "Game.h"
#include <iostream>

Game::Game(int screenwidth, int screenheight) {
	width = screenwidth;
	height = screenheight;
	cellsize = height / 20;
	level = 0;
	score = 0;
	lines_cleared = 1;
}

// todo - move everything to the constructor
int Game::Init(const char* title) {

	//set constants
	InitWindow(width, height, title);
	SetTargetFPS(30);
	window_icon = LoadImage("../assets/tetris-logo.png");
	printf("%d\n", IsImageReady(window_icon));
	SetWindowIcon(window_icon);

	last_update_time = 0.0f;
	current_block = new Block(5, 1, false);
	next_block = new Block(13, 5, false);
	estimation = new Block(5, 1, false);
	on_hold = new Block(13, 14, true);

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

bool Game::EventTriggered(float interval) {

	float current_time = (float)GetTime();
	if (current_time - last_update_time >= interval) {
		last_update_time = current_time;
		return true;
	}
	return false;
}

void Game::Render() {
	ClearBackground(BLACK);

	//render game grid
	grid.Render(cellsize);	

	//game ui --> logo + gradient
	DrawText("Tetris", 10 * cellsize + cellsize/5, cellsize/10, 2*cellsize-cellsize/5, WHITE);
	DrawRectangleGradientH(3 * cellsize, 0, width - 3 * cellsize, height, { 100,0,235,0 }, { 100,0,235,145 });
	
	//separating line (field | info)
	DrawLine(10*cellsize, 0, 10*cellsize, height, { 160, 160, 180, 255 });

	//current block rendering
	current_block->Render(cellsize);

	//estimated fall rendering
	estimation->ChangeColorBy(0,0,0 , -175);
	estimation->Render(cellsize);

	//next_block visuals
	DrawRectangleRoundedLines({10.5f*cellsize, 2.0f*cellsize-cellsize/5.0f,  5.0f* cellsize, 3.5f* cellsize},0.1f, 8, cellsize/10.0f, WHITE);		//next -boundry
	DrawText("Next:", 11 * cellsize, 2 * cellsize+cellsize/10, (cellsize/5)*4, WHITE);	//next -text
	next_block->Render(cellsize);	//next -piece

	//game (difficulty) level visuals
	DrawRectangleRoundedLines({ 10.5f * cellsize, 6.0f * cellsize - cellsize / 5.0f,  5.0f * cellsize, 1.5f * cellsize }, 0.1f, 8, cellsize / 10.0f, WHITE);	//score -boundry
	DrawText(TextFormat("Level %i", level), 11 * cellsize, 6 * cellsize + cellsize / 10, (cellsize / 5) * 4, WHITE);	//score -points

	//block on hold visuals
	if (!on_hold->is_uninitialized) {
		DrawRectangleRoundedLines({ 10.5f * cellsize, 11.0f * cellsize - cellsize / 5.0f,  5.0f * cellsize, 3.5f * cellsize }, 0.1f, 8, cellsize / 10.0f, WHITE);		//next -boundry
		DrawText("Hold:", 11 * cellsize, 11 * cellsize + cellsize / 10, (cellsize / 5) * 4, WHITE);	//next -text
		on_hold->Render(cellsize);
	}

	//case of game over
	if (grid.isGameOver()) {
		GameOverScreen();
		if (IsKeyPressed(KEY_ENTER)) {
			grid.Clear();
			score = 0;
		}
	}
	
	//draw achieved score over game_over screen
	DrawRectangleRoundedLines({ 10.5f * cellsize, 8.0f*cellsize -cellsize/5.0f,  5.0f * cellsize, 2.5f * cellsize }, 0.1f, 8, cellsize/10.0f, WHITE);	//score -boundry
	DrawText("Score:", 11 * cellsize, 8 * cellsize + cellsize / 10, (cellsize / 5) * 4, WHITE);	//score -text
	DrawText(TextFormat("   %i", score), 11 * cellsize, 9 * cellsize + cellsize / 10, (cellsize/5)*4, WHITE);	//score -points
}

void Game::Run() {

	// randomise the used blocks
	next_block->Randomise((int)this);
	current_block->Randomise((int)this);

	//LoadingScreen();
	
	// main game loop

	while (!ShouldClose()) {
		*estimation = *current_block;
		estimation->HardDrop(&grid);

		// render everything
		BeginDrawing();
			this->Render();
		EndDrawing();

		// for passive block falling
		if (EventTriggered(0.5f)) {
			current_block->UpdatePositionPassive(&grid);
		}

		//case of block hitting the ground
		if (current_block->IsPlaced(&grid)) {
			current_block->Join(&grid);
			*current_block = *next_block;
			current_block->SetCoords(5, 1);
			next_block->Randomise((unsigned int)last_update_time);
		}

		// update position according to inputs
		this->HandleInput();


		// clear the lines and update score accordingly
		score += grid.ClearLines(level);
	}

}

void Game::HandleInput() {
	int modifier = 0;
	int key_pressed = GetKeyPressed();
	if (key_pressed == KEY_A || key_pressed == KEY_LEFT) {
		modifier--;
	}
	if (key_pressed == KEY_D || key_pressed == KEY_RIGHT) {
		modifier++;
	}

	current_block->axis.x += modifier;
	if (current_block->DoesIntersect(&grid))
		current_block->axis.x -= modifier;

	if (key_pressed == KEY_S || key_pressed == KEY_DOWN)
		current_block->UpdatePositionPassive(&grid);

	if (IsKeyPressed(KEY_SPACE)) {
		current_block->RotateRight(&grid);
	}

	if (key_pressed == KEY_W || key_pressed == KEY_UP) {

		Coords current_block_coords = current_block->axis;

		// in case it hasnt been used yet - must also randomize the next block
		if (on_hold->is_uninitialized) {
			*on_hold = *current_block;
			*current_block = *next_block;

			//to prevent crashing in the if statement
			current_block->axis = current_block_coords;

			//checking if it is possible to switch the block
			if (current_block->DoesIntersect(&grid)) {
				*current_block = *on_hold;
				*on_hold = *next_block;
				on_hold->is_uninitialized = true;
			}
			else {
				next_block->Randomise((unsigned int)last_update_time);
				on_hold->is_uninitialized = false;
			}
		}
		else {
			Block temp1 = *current_block;
			Block temp2 = *on_hold;
			*current_block = *on_hold;

			//to prevent crashing in the if statement
			current_block->axis = current_block_coords;

			//checking if it is possible to switch the block
			if (current_block->DoesIntersect(&grid)) {
				*current_block = temp1;
			}
			//else reset the block on hold
			else {
				*on_hold = temp1;
			}
		}
		//default the block on hold regardless
		on_hold->state = 0;

		//reset the coords regardless
		on_hold->SetCoords(13, 14);
		current_block->axis = current_block_coords;
	}

	if (key_pressed == KEY_TAB || key_pressed == KEY_RIGHT_SHIFT) {
		current_block->HardDrop(&grid);
	}

}

Game::~Game() {
	delete on_hold;
	delete estimation;
	delete next_block;
	delete current_block;
	CloseWindow();
}