// FillArray.cpp : Defines the functions for the static library.
//

#include "FillArray.h"

// TODO: This is an example of a library function
void fillArray(std::array<std::array<int, maxColumns>, maxRows>& array, size_t rows, size_t columns)
{
	int value = 0;
	bool toDown = true;
	int row = 0;
	int column = 0;
	int iteration = 0;
	while ((row + column) != (rows + columns))
	{
		if (toDown)
		{
			if (iteration < columns)
			{
				column = iteration;
				row = 0;
			}
			else
			{
				column = columns - 1;
				row = iteration - columns + 1;
			}
			while (row < rows && column >= 0)
			{
				array[row][column] = ++value;
				row++;
				column--;
			}
			toDown = false;
		}
		else
		{
			if (iteration < rows)
			{
				row = iteration;
				column = 0;
			}
			else
			{
				row = rows - 1;
				column = iteration - rows + 1;
			}
			while (row>=0 && column<columns)
			{
				array[row][column] = ++value;
				column++;
				row--;
			}
			toDown = true;
		}
		iteration++;
	}
}

