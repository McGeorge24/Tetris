#pragma once
#include "Core.h"

class Grid
{
public:
	char** grid;

	Grid();
	~Grid();
	int ClearLines(int level, int * lines_cleared_total);
	void Clear();
	void Render(int cell_size);
	bool isGameOver();

	char GetValue(int x, int y) const;
	int SetValue(int x, int y, colors color);
};

