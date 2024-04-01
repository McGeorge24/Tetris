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


Block::Block(float x, float y) {
	coords = { x,y };
	axis = { (int)round(x), (int)round(y) };
	color_value = gray;
	color_RGBA = { 0,0,0,0 };
	unit[0] = { 0,0 }; unit[1] = { 0,0 }; unit[2] = { 0,0 }; unit[3] = { 0,0 };
	shape = O;
	speed = 2.0f;
}

void Block::Randomise(unsigned int seed) {
	srand(seed);
	shape = (Shapes)(rand() % 7);
	DefineShape(unit, shape);
	color_value = (colors)(rand() % 7 + 1);
	color_RGBA = toRGBA(color_value);
}

void Block::SetCoords(int x, int y) {
	coords = { (float)x, (float)y };
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

bool Block::IsPlaced(Grid * grid) {
	if (grid->GetValue(axis.x + unit[0].x, axis.y + 1 + unit[0].y) == 0 &&
		grid->GetValue(axis.x + unit[1].x, axis.y + 1 + unit[1].y) == 0 &&
		grid->GetValue(axis.x + unit[2].x, axis.y + 1 + unit[2].y) == 0 &&
		grid->GetValue(axis.x + unit[3].x, axis.y + 1 + unit[3].y) == 0)
		return false;
	else
		return true;
}

void Block::UpdatePositionPassive(float delta_time) {
	coords.y+= delta_time*speed;
	axis.y = round(coords.y);
}


void Block::UpdatePosition(Grid * grid) {
	float modifier = 0;
	if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
		modifier -= 0.1;
	}
	if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
		modifier += 0.1;
	}

	coords.x += speed * modifier;
	axis.x = round(coords.x);
	if (grid->GetValue(axis.x + unit[0].x, axis.y + 1 + unit[0].y) != 0 ||
		grid->GetValue(axis.x + unit[1].x, axis.y + 1 + unit[1].y) != 0 ||
		grid->GetValue(axis.x + unit[2].x, axis.y + 1 + unit[2].y) != 0 ||
		grid->GetValue(axis.x + unit[3].x, axis.y + 1 + unit[3].y) != 0)
		coords.x -= speed * modifier;
	axis.x = round(coords.x);
	if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
		UpdatePositionPassive(0.1f);
	
}

Coords Block::GetCoords() {
	return axis;
}

void Block::SetCoords(Coords coords) {
	this->axis = coords;
}

void Block::HardDrop(Grid * grid) {
	while (!IsPlaced(grid)) {
		axis.y++;
	}
}

void Block::ChangeColorBy(char r, char g, char b, char a) {
	color_RGBA.r += r;
	color_RGBA.g += g;
	color_RGBA.b += b;
	color_RGBA.a += a;
}


void Block::Join(Grid* grid) {
	grid->SetValue(axis.x + unit[0].x, axis.y + unit[0].y, color_value);
	grid->SetValue(axis.x + unit[1].x, axis.y + unit[1].y, color_value);
	grid->SetValue(axis.x + unit[2].x, axis.y + unit[2].y, color_value);
	grid->SetValue(axis.x + unit[3].x, axis.y + unit[3].y, color_value);
}