#include "Grid.h"
#include "Core.h"

Grid::Grid() {
	grid = new char* [22];
	
	for (int i = 0; i < 22; i++) 
	{
		grid[i] = new char[12];
		
		for (int j = 1; j < 11; j++) {	//set 1-10 to black
			grid[i][j] = 0;
		}
	}
	for (int j = 0; j < 12; j++) //set last line to white - border
	{
		grid[21][j] = 8;	
	}
	for (int i = 0; i < 22; i++)	//set first an last column to white - border
	{
		grid[i][0] = 8;
		grid[i][11] = 8;
	}
}
Grid::~Grid() {
	for (int i = 0; i < 22; i++) {
		delete[] grid[i];
	}
	delete[] grid;
}

void Grid::ClearLines(int * score) {
	bool is_full;	//for 1 line

	for (int y = 1; y < 21; y++) {

		is_full = true;

		for (int x = 1; x < 11; x++) {
			//if at least 1 cell is black
			if (grid[y][x] == (char)black) {
				is_full = false;
				break;
			}
		}

		if (is_full) {
			(*score)++;
			for (int i = y; i > 0; i--) {
				for (int j = 1; j < 11; j++) {
					grid[i][j] = grid[i - 1][j];
				}
			}
		}
		
	}
}

void Grid::Render(int cell_size) {	//works flawless
	for (int y = 1; y < 22; y++) {
		for (int x = 1; x < 11; x++) {
			Color color = toRGBA((colors)(grid[y][x]));
			DrawUnit(x-1, y-1, cell_size, color);
		}
	}
}


bool Grid::isGameOver() {	//works flawless
	for (int i = 1; i < 11; i++) {
		if (grid[1][i]) {
			return true;
		}
	}
	return false;
}


char Grid::GetValue(int x, int y) const {
	return grid[y][x];
}


int Grid::SetValue(int x, int y, colors color) {
	grid[y][x] = color;
	return 1;
}