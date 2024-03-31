#pragma once
#include <raylib.h>

enum colors {
	black, red, orange, yellow, green, cyan, blue, violet, white
};

struct Coords {
	int x;
	int y;
};

Color toRGBA(colors color);

void DrawUnit(int x, int y, int cell_size, Color color); //x,y meaning which cell, not pixel coord