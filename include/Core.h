#pragma once
#include <raylib.h>

enum colors {
	gray, red, orange, yellow, green, cyan, blue, violet, white
};

struct Coords {
	char x;
	char y;
};

struct Tetromino {
	Coords parts[4];
};

Color toRGBA(colors color);

void DrawUnit(int x, int y, int cell_size, Color color); //x,y meaning which cell, not pixel coord