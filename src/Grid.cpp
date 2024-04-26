#include "Grid.h"

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
		grid[0][j] = 0;
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

int Grid::ClearLines(int level) {
	bool is_full;
	int lines_cleared = 0;

	for (int y = 1; y < 21; y++) {

		//check if the line is full
		is_full = true;
		for (int x = 1; x < 11; x++) {
			if (grid[y][x] == 0) {
				is_full = false;
				break;
			}
		}

		//move lines down if it is full
		if (is_full) {
			lines_cleared++;

			for (int i = y; i > 0; i--) {
				for (int x = 1; x < 11; x++) {
					grid[i][x] = grid[i - 1][x];
				}
			}
		}
	}

	switch (lines_cleared) {
	default:
		return 0;
	case 1:
		return 40 * (level + 1);
	case 2:
		return 100 * (level + 1);
	case 3:
		return 300 * (level + 1);
	case 4:
		return 1200 * (level + 1);
	}

	//todo rework ClearLines
}

void Grid::Clear() {
	for (int i = 0; i < 21; i++) {
		for (int j = 1; j < 11; j++) {
			grid[i][j] = 0;
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