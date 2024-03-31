#include "Block.h"
#include <stdlib.h>
#include <iostream>


void DefineShape(Coords* unit, Shapes shape) {
	if (shape == O) 
	{
		unit[0] = { -1, -1 };
		unit[1] = { 0, -1 };
		unit[2] = { -1, 0 };
		unit[3] = { 0, 0 };
	}
	else if (shape == I) 
	{
		unit[0] = { -1, 0 };
		unit[1] = { 0, 0 };
		unit[2] = { 1, 0 };
		unit[3] = { 2, 0 };
	}
	else if (shape == Z) 
	{
		unit[0] = { -1, -1 };
		unit[1] = { 0, -1 };
		unit[2] = { 0, 0 };
		unit[3] = { 1, 0 };
	}
	else if (shape == S) 
	{
		unit[0] = { -1, 0 };
		unit[1] = { 0, 0 };
		unit[2] = { 0, -1 };
		unit[3] = { 1, -1 };
	}
	else if (shape == T)
	{
		unit[0] = { 0, 0 };
		unit[1] = { -1, 0 };
		unit[2] = { 0, -1 };
		unit[3] = { 1, 0 };
	}
	else if (shape == J) 
	{
		unit[0] = { -1, -1 };
		unit[1] = { -1, 0 };
		unit[2] = { 0, 0 };
		unit[3] = { 1, 0 };
	}
	else
	{
		unit[0] = { -1, 0 };
		unit[1] = { 0, 0 };
		unit[2] = { 1, 0 };
		unit[3] = { 1, -1 };
	}
	/*
	std::cout << shape << std::endl;
	std::cout << unit[0].x << unit[0].y << std::endl;
	std::cout << unit[1].x << unit[1].y << std::endl;
	std::cout << unit[2].x << unit[2].y << std::endl;
	std::cout << unit[3].x << unit[3].y << std::endl;
	*/
}


Block::Block(int x, int y) {	//other stuff is initialized when .Randomise() is called
	axis = { x,y };
	is_placed = false;
	color_value = black;
	color_RGBA = { 0,0,0,0 };
	unit[0] = { 0,0 }; unit[1] = { 0,0 }; unit[2] = { 0,0 }; unit[3] = { 0,0 };
	shape = O;
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
	DrawUnit(axis.x - 1 + unit[0].x, axis.y - 1 + unit[0].y, cell_size, color_RGBA);
	DrawUnit(axis.x - 1 + unit[1].x, axis.y - 1 + unit[1].y, cell_size, color_RGBA);
	DrawUnit(axis.x - 1 + unit[2].x, axis.y - 1 + unit[2].y, cell_size, color_RGBA);
	DrawUnit(axis.x - 1 + unit[3].x, axis.y - 1 + unit[3].y, cell_size, color_RGBA);
}

void Block::RotateRight() {

}

void Block::Update_Y_Position(char ** grid) {
	if (grid[axis.y + 2 + unit[0].y][axis.x + unit[0].x] == 0 && 
		grid[axis.y + 2 + unit[1].y][axis.x + unit[1].x] == 0 && 
		grid[axis.y + 2 + unit[2].y][axis.x + unit[2].x] == 0 && 
		grid[axis.y + 2 + unit[3].y][axis.x + unit[3].x] == 0)
		axis.y++;
	else
		is_placed = true;
}


void Block::Update_X_Position(char ** grid) {
	int modifier = 0;
	if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
		axis.x--;
		modifier = 1;
	}
	if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
		axis.x++;
		modifier = -1;
	}

	//printf("%x", grid);
	
	if (grid[axis.y + unit[0].y][axis.x + unit[0].x] != 0 ||
		grid[axis.y + unit[1].y][axis.x + unit[1].x] != 0 ||
		grid[axis.y + unit[2].y][axis.x + unit[2].x] != 0 ||
		grid[axis.y + unit[3].y][axis.x + unit[3].x] != 0)
		axis.x += modifier;
	/*
	if (grid->GetValue(axis.x + unit[0].x - 1, axis.y + unit[0].y) > 0 ||
		grid->GetValue(axis.x + unit[1].x - 1, axis.y + unit[1].y) > 0 ||
		grid->getValue(axis.x + unit[2].x - 1, axis.y + unit[2].y) > 0 ||
		grid->getValue(axis.x + unit[3].x - 1, axis.y + unit[3].y) > 0 )
		axis.x += modifier;
	
	else if (grid->getValue(axis.x + unit[0].x + 1, axis.y + unit[0].y) > 0 ||
			 grid->getValue(axis.x + unit[1].x + 1, axis.y + unit[1].y) > 0 ||
			 grid->getValue(axis.x + unit[2].x + 1, axis.y + unit[2].y) > 0 ||
			 grid->getValue(axis.x + unit[3].x + 1, axis.y + unit[3].y) > 0)
			 axis.x--;
	*/
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