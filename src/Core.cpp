#include "Core.h"
#include <iostream>

Color toRGBA(colors color) {
	switch (color) {
	case black:
		return {30, 30, 30, 150};
	case red:
		return RED;
	case orange:
		return ORANGE;
	case yellow:
		return YELLOW;
	case green:
		return GREEN;
	case cyan:
		return SKYBLUE;
	case blue:
		return BLUE;
	case violet:
		return PURPLE;
	default:
		return WHITE;
	}
}

void DrawUnit(int x, int y, int cell_size, Color color) //x,y meaning which cell, not pixel coord
{
	DrawRectangle(x * cell_size + 5, y * cell_size + 5, cell_size - 10, cell_size - 10, color);
	color.a -= 100;
	DrawRectangle(x * cell_size, y * cell_size, cell_size, cell_size, color);
	//DrawText(TextFormat("%i, %i", x, y), x*cell_size+5, y*cell_size+5, 10, WHITE);
}