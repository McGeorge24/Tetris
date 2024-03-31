#include <raylib.h>
#include "Screen.h"

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
		DrawText("Tetris", 185, 480, 40, {(unsigned char)i, (unsigned char)i, (unsigned char)i, (unsigned char)i});
		EndDrawing();
	}
}

void Screen::GameOverScreen() {
	DrawRectangle(0, 0, width, height, { 0, 0, 0, 192 });
	DrawText("Game over", 115, height / 2 - 25, 50, { 255, 0, 0, 192 });
}

void Screen::Update(Grid * grid, Block * block, Block * next, float * delta_time) {

	ClearBackground(BLACK);
	grid->Render(50);
	DrawRectangleGradientH(width-300, 0, 300, height, { 127,0,255,0 }, { 127,0,255,145 });
	next->Render(50);
	DrawText("Next:", 11 * 50+5, 3 * 50+5, 40, WHITE);

	if (grid->isGameOver()) {
		GameOverScreen();
	}
	else {
		if (block->is_placed) {
			block->Render(50);
			block->Join(grid);
			*block = *next;
			block->SetCoords(5, 0);
			next->Randomise((unsigned int)((*delta_time) * 10000*width));
		}	
		if (*delta_time > 0.1f) {
			block->Update_Y_Position(grid->GetPointer());
			(*delta_time) -= 0.1f;
		}
		block->Render(50);
		grid->ClearLines();
		block->Update_X_Position();
	}
}

Screen::~Screen() {
	CloseWindow();
}