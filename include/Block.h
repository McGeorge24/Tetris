#pragma once
#include "Grid.h"

enum Shapes {
	O, I, Z, S, T, J, L
};

void DefineShape(Coords* units, Shapes shape);

class Block
{
public:

	bool is_uninitialized;
	Coords axis;		//position of the base unit (with unit offset 0,0)
	char state; //for rotation

	Block(char x, char y, bool is_uninitialized);
	void Randomise(unsigned int seed);
	void SetCoords(int x, int y);
	void Render(int cell_size);
	void RotateRight(Grid * grid);
	bool IsPlaced(Grid * grid);
	void UpdatePositionPassive(Grid * grid);
	void HandleInput(Grid * grid, Block * held);
	void ChangeColorBy(char r, char g, char b, char a);
	bool DoesIntersect(Grid * grid);
	//Coords GetCoords();
	void HardDrop(Grid * grid);
	void Join(Grid* grid);

private:

	Coords unit[16];		//offset of every subunit
	char rotation_states;				//how many rotation states, which rotation state
	Color color_RGBA;
	colors color_value;
	Shapes shape;
};

