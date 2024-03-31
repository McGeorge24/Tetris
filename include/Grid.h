#pragma once
#include "Core.h"

class Grid
{
public:
	char** grid;
	Grid();
	~Grid();
	void ClearLines();
	void Render(int cell_size);
	bool isGameOver();

	char** GetPointer();
	int SetValue(int x, int y, colors color);
};

