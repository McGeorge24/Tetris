#pragma once
#include "Core.h"

class Grid
{
public:
	char** grid;

	Grid();
	~Grid();
	void ClearLines(int * score);
	void Clear();
	void Render(int cell_size);
	bool isGameOver();

	char GetValue(int x, int y) const;
	int SetValue(int x, int y, colors color);
};

