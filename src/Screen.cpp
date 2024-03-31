#include <raylib.h>
#include "Screen.h"
#include <iostream>

Screen::Screen(int screenwidth, int screenheight) {
	width = screenwidth;
	height = screenheight;
}

int Screen::Init(const char* title) {
	InitWindow(width, height, title);
	SetTargetFPS(60);
	return 1;
}

bool Screen::ShouldClose() {
	return WindowShouldClose();
}

void Screen::LoadingScreen() {
	for (int i = 0; i < 256; i+=1) {
		BeginDrawing();
		ClearBackground(BLACK);
		DrawText("Tetris", width/2-85, 480, 40, {(unsigned char)i, (unsigned char)i, (unsigned char)i, (unsigned char)i});
		EndDrawing();
	}
}

void Screen::GameOverScreen() {
	DrawRectangle(0, 0, width-300, height, { 0, 0, 0, 192 });
	DrawRectangleGradientH(width-300, 0, 300, height, { 0,0,0,190 }, { 0,0,0,60 });
	DrawText("Game over", 115, height / 2 - 25, 50, { 255, 0, 0, 192 });
}

void Screen::Update(Grid * grid, Block * block, Block * next, float * delta_time, int * score) {

	ClearBackground(BLACK);
	grid->Render(50);	//render game grid
	DrawRectangleGradientH(150, 0, width-150, height, { 100,0,235,0 }, { 100,0,235,145 });	//gradient over it
	DrawLineEx({ 10.0*50+3, 0.0 }, { 10.0*50+3, 1.0f * height }, 5.0f, {160, 160, 180, 255});	//separating line
	DrawRectangleRoundedLines({10.5*50, 1.0*90,  5.0* 50, 3.5* 50},0.1f, 8, 5.0f, WHITE);		//next -boundry
	DrawText("Next:", 11 * 50, 2 * 50+5, 40, WHITE);	//next -text
	next->Render(50);	//next -piece

	if (grid->isGameOver()) {
		GameOverScreen();
	}
	else 
	{
		if (block->is_placed) {
			block->Render(50);
			block->Join(grid);
			*block = *next;
			block->SetCoords(5, 1);
			next->Randomise((unsigned int)((*delta_time) * 10000*width));
		}	
		if (*delta_time > 0.1f) {
			block->Update_X_Position(grid->grid);
			block->Update_Y_Position(grid->grid);
			(*delta_time) -= 0.1f;
		}
		block->Render(50);
		grid->ClearLines(score);
	}

	//draw over potential game over screen
	DrawRectangleRoundedLines({ 10.5 * 50, 1.0 * 290,  5.0 * 50, 2.5 * 50 }, 0.1f, 8, 5.0f, WHITE);	//score -boundry
	DrawText("Score:", 11 * 50, 6 * 50 + 5, 40, WHITE);	//score -text
	DrawText(TextFormat("   %i", *score), 11 * 50, 7 * 50 + 5, 40, WHITE);	//score -points
}

Screen::~Screen() {
	CloseWindow();
}