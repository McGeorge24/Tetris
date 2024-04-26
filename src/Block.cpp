#include "Block.h"
#include <stdlib.h>
#include <iostream>


void DefineShape(Coords * unit, char * rotation_states, Shapes shape) {
	if (shape == O) 
	{
		unit[0] = { -1, -1 };
		unit[1] = { 0, -1 };
		unit[2] = { -1, 0 };
		unit[3] = { 0, 0 };
		*rotation_states = 1;
	}
	else if (shape == I) 
	{
		unit[0] = { -1, 0 };
		unit[1] = { 0, 0 };
		unit[2] = { 1, 0 };
		unit[3] = { 2, 0 };

		unit[4] = { 0, -1 };
		unit[5] = { 0, 0 };
		unit[6] = { 0, 1 };
		unit[7] = { 0, 2 };
		*rotation_states = 2;
	}
	else if (shape == Z) 
	{
		unit[0] = { -1, -1 };
		unit[1] = { 0, -1 };
		unit[2] = { 0, 0 };
		unit[3] = { 1, 0 };
		
		unit[4] = { -1, 1 };
		unit[5] = { -1, 0 };
		unit[6] = { 0, 0 };
		unit[7] = { 0, -1 };

		*rotation_states = 2;
	}
	else if (shape == S) 
	{
		unit[0] = { -1, 0 };
		unit[1] = { 0, 0 };
		unit[2] = { 0, -1 };
		unit[3] = { 1, -1 };

		unit[4] = { 1, 1 };
		unit[5] = { 1, 0 };
		unit[6] = { 0, 0 };
		unit[7] = { 0, -1 };

		*rotation_states = 2;
	}
	else if (shape == T)
	{
		unit[0] = { 0, 0 };
		unit[1] = { -1, 0 };
		unit[2] = { 0, -1 };
		unit[3] = { 1, 0 };

		unit[4] = { 0, 1 };
		unit[5] = { 1, 0 };
		unit[6] = { 0, 0 };
		unit[7] = { 0, -1 };
		
		unit[8] = { 0, 0 };
		unit[9] = { 1, 0 };
		unit[10] = { 0, 1 };
		unit[11] = { -1, 0 };

		unit[12] = { 0, 1 };
		unit[13] = { -1, 0 };
		unit[14] = { 0, 0 };
		unit[15] = { 0, -1 };
		
		*rotation_states = 4;
	}
	else if (shape == J) 
	{
		unit[0] = { -1, -1 };
		unit[1] = { -1, 0 };
		unit[2] = { 0, 0 };
		unit[3] = { 1, 0 };
		
		unit[4] = { 1, -1 };
		unit[5] = { 0, -1 };
		unit[6] = { 0, 0 };
		unit[7] = { 0, 1 };

		unit[8] = { -1, 0 };
		unit[9] = { 0, 0 };
		unit[10] = { 1, 0 };
		unit[11] = { 1, 1 };

		unit[12] = { 0, -1 };
		unit[13] = { 0, 0 };
		unit[14] = { 0, 1 };
		unit[15] = { -1, 1 };

		*rotation_states = 4;
	}
	// L-shape
	else
	{
		unit[0] = { -1, 0 };
		unit[1] = { 0, 0 };
		unit[2] = { 1, 0 };
		unit[3] = { 1, -1 };
		
		unit[4] = { 0, -1 };
		unit[5] = { 0, 0 };
		unit[6] = { 0, 1 };
		unit[7] = { 1, 1 };

		unit[8] = { 1, 0 };
		unit[9] = { 0, 0 };
		unit[10] = { -1, 0 };
		unit[11] = { -1, 1 };

		unit[12] = { -1, -1 };
		unit[13] = { 0, -1 };
		unit[14] = { 0, 0 };
		unit[15] = { 0, 1 };

		*rotation_states = 4;
	}
}


Block::Block(char x, char y, bool is_uninitialized) {
	axis = { x, y };
	color_value = gray;
	color_RGBA = { 0,0,0,0 };
	for (int i = 0; i < 16; i++) {
		unit[i] = { 0,0 };
	}
	shape = O;
	rotation_states = 0;
	state = 0;
	this->is_uninitialized = is_uninitialized;
}

bool Block::DoesIntersect(Grid * grid) {
	if (grid->GetValue(axis.x + unit[state * 4 + 0].x, axis.y + unit[state * 4 + 0].y) != 0 ||
		grid->GetValue(axis.x + unit[state * 4 + 1].x, axis.y + unit[state * 4 + 1].y) != 0 ||
		grid->GetValue(axis.x + unit[state * 4 + 2].x, axis.y + unit[state * 4 + 2].y) != 0 ||
		grid->GetValue(axis.x + unit[state * 4 + 3].x, axis.y + unit[state * 4 + 3].y) != 0)
		return true;
	else
		return false;
}

void Block::Randomise(unsigned int seed) {
	srand(seed);
	shape = (Shapes)(rand() % 7);
	DefineShape(unit, &rotation_states, shape);
	color_value = (colors)(rand() % 7 + 1);
	color_RGBA = toRGBA(color_value);
}

void Block::SetCoords(int x, int y) {
	axis.x = x;
	axis.y = y;
}

void Block::Render(int cell_size) {
	DrawUnit(axis.x - 1 + unit[state * 4 + 0].x, axis.y - 1 + unit[state * 4 + 0].y, cell_size, color_RGBA);
	DrawUnit(axis.x - 1 + unit[state * 4 + 1].x, axis.y - 1 + unit[state * 4 + 1].y, cell_size, color_RGBA);
	DrawUnit(axis.x - 1 + unit[state * 4 + 2].x, axis.y - 1 + unit[state * 4 + 2].y, cell_size, color_RGBA);
	DrawUnit(axis.x - 1 + unit[state * 4 + 3].x, axis.y - 1 + unit[state * 4 + 3].y, cell_size, color_RGBA);
}

void Block::RotateRight(Grid * grid) {
	short old_state = state;
	state += 1;
	state = state % rotation_states;
	if (DoesIntersect(grid)) state = old_state;
}

bool Block::IsPlaced(Grid * grid) {
	if (grid->GetValue(axis.x + unit[state * 4 + 0].x, axis.y + 1 + unit[state * 4 + 0].y) == 0 &&
		grid->GetValue(axis.x + unit[state * 4 + 1].x, axis.y + 1 + unit[state * 4 + 1].y) == 0 &&
		grid->GetValue(axis.x + unit[state * 4 + 2].x, axis.y + 1 + unit[state * 4 + 2].y) == 0 &&
		grid->GetValue(axis.x + unit[state * 4 + 3].x, axis.y + 1 + unit[state * 4 + 3].y) == 0)
		return false;
	else
		return true;
}

void Block::UpdatePositionPassive(Grid * grid) {
	axis.y++;
	if (DoesIntersect(grid)) {
		axis.y--;
	}
}


void Block::HandleInput(Grid * grid, Block * held) {
	//located at game.HandleInput();
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
	grid->SetValue(axis.x + unit[state * 4 + 0].x, axis.y + unit[state * 4 + 0].y, color_value);
	grid->SetValue(axis.x + unit[state * 4 + 1].x, axis.y + unit[state * 4 + 1].y, color_value);
	grid->SetValue(axis.x + unit[state * 4 + 2].x, axis.y + unit[state * 4 + 2].y, color_value);
	grid->SetValue(axis.x + unit[state * 4 + 3].x, axis.y + unit[state * 4 + 3].y, color_value);
}