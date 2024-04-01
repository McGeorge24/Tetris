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
	Vector2 coords;
	Coords axis;		//for accessing the grid
	Color color_RGBA;
	colors color_value;
	Shapes shape;
	float speed;

public:

	Block(float x, float y);
	void Randomise(unsigned int seed);
	void SetCoords(int x, int y);
	void Render(int cell_size);
	void RotateRight();
	bool IsPlaced(Grid * grid);
	void UpdatePositionPassive(float delta_time);
	void UpdatePosition(Grid * grid);
	void ChangeColorBy(char r, char g, char b, char a);
	Coords GetCoords();
	void SetCoords(Coords coords);
	void HardDrop(Grid * grid);
	void Join(Grid* grid);
};

