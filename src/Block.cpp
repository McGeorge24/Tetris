#include "Block.h"
#include <stdlib.h>
//#include <iostream>


void DefineShape(Coords* units, Shapes shape) {
	if (shape == O) 
	{
		units[0] = { -1, -1 };
		units[1] = { 0, -1 };
		units[2] = { -1, 0 };
		units[3] = { 0, 0 };
	}
	else if (shape == I) 
	{
		units[0] = { -2, 0 };
		units[1] = { -1, 0 };
		units[2] = { 0, 0 };
		units[3] = { 1, 0 };
	}
	else if (shape == Z) 
	{
		units[0] = { -1, -1 };
		units[1] = { 0, -1 };
		units[2] = { 0, 0 };
		units[3] = { 1, 0 };
	}
	else if (shape == S) 
	{
		units[0] = { -1, 0 };
		units[1] = { 0, 0 };
		units[2] = { 0, -1 };
		units[3] = { 1, -1 };
	}
	else if (shape == T)
	{
		units[0] = { 0, 0 };
		units[1] = { -1, 0 };
		units[2] = { 0, -1 };
		units[3] = { 1, 0 };
	}
	else if (shape == J) 
	{
		units[0] = { -1, -1 };
		units[1] = { -1, 0 };
		units[2] = { 0, 0 };
		units[3] = { 1, 0 };
	}
	else
	{
		units[0] = { -1, 0 };
		units[1] = { 0, 0 };
		units[2] = { 1, 0 };
		units[3] = { 1, -1 };
	}
	/*
	std::cout << shape << std::endl;
	std::cout << units[0].x << units[0].y << std::endl;
	std::cout << units[1].x << units[1].y << std::endl;
	std::cout << units[2].x << units[2].y << std::endl;
	std::cout << units[3].x << units[3].y << std::endl;
	*/
}


Block::Block(int x, int y) {	//other stuff is initialized when .Randomise() is called
	axis = { x,y };
	is_placed = false;
}

void Block::Randomise(unsigned int seed) {
	srand(seed);
	shape = (Shapes)(rand() % 7);
	DefineShape(unit, shape);
	color_value = (colors)(rand() % 7 + 1);
	color_RGBA = toRGBA(color_value);
}

void Block::SetCoords(int x, int y) {
	axis.x = x;
	axis.y = y;
}

void Block::Render(int cell_size) {
	DrawUnit(axis.x - 1 + unit[0].x, axis.y + unit[0].y, cell_size, color_RGBA);
	DrawUnit(axis.x - 1 + unit[1].x, axis.y + unit[1].y, cell_size, color_RGBA);
	DrawUnit(axis.x - 1 + unit[2].x, axis.y + unit[2].y, cell_size, color_RGBA);
	DrawUnit(axis.x - 1 + unit[3].x, axis.y + unit[3].y, cell_size, color_RGBA);
}

void Block::RotateRight() {

}

void Block::Update_Y_Position(char ** grid) {
	if (grid[axis.y + 2 + unit[0].y][axis.x + unit[0].x] == 0 && grid[axis.y + 2 + unit[1].y][axis.x + unit[1].x] == 0 && grid[axis.y + 2 + unit[2].y][axis.x + unit[2].x] == 0 && grid[axis.y + 2 + unit[3].y][axis.x + unit[3].x] == 0)
		axis.y++;
	else
		is_placed = true;
}


void Block::Update_X_Position() {
	if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) {
		axis.x--;
	}
	if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) {
		axis.x++;
	}
	if (axis.x + unit[0].x < 1 || axis.x + unit[1].x < 1 || axis.x + unit[2].x < 1 || axis.x + unit[3].x < 1) {
		axis.x++;
	}
	else if ()
	else if (axis.x + unit[0].x > 10 || axis.x + unit[1].x > 10 || axis.x + unit[2].x > 10 || axis.x + unit[3].x > 10) {
		axis.x--;
	}
}


void Block::Join(Grid* grid) {
	grid->SetValue(axis.x + unit[0].x, axis.y + 1 + unit[0].y, color_value);
	grid->SetValue(axis.x + unit[1].x, axis.y + 1 + unit[1].y, color_value);
	grid->SetValue(axis.x + unit[2].x, axis.y + 1 + unit[2].y, color_value);
	grid->SetValue(axis.x + unit[3].x, axis.y + 1 + unit[3].y, color_value);
	axis.y = 0;
	axis.x = 5;
	is_placed = false;
}