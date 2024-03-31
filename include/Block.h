#pragma once
#include "Grid.h"

enum Shapes {
	O, I, Z, S, T, J, L
};

void DefineShape(Coords* units, Shapes shape);

class Block
{
private:
	Coords unit[4];		//offset of every subunit
	Coords axis;		//aslo coords
	Color color_RGBA;
	colors color_value;
	Shapes shape;

public:

	bool is_placed;

	Block(int x, int y);
	void Randomise(unsigned int seed);
	void SetCoords(int x, int y);
	void Render(int cell_size);
	void RotateRight();
	void Update_Y_Position(char ** grid);
	void Update_X_Position();
	void Join(Grid* grid);
};

