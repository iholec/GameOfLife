#include "stdafx.h"
#include "GOLField.h"
#include <string>
#include <iostream>

GOLField::GOLField(char ** read_field, const int width, const int height)
{
	field_ = new char * [height + 1];
	field_minus_one_ = new char * [height + 1];
	height_ = height;//todo remove
	width_ = width;//todo remove

	for (int i = 0; i < height; ++i)
	{
		field_[i] = new char[width + 1];
		field_minus_one_[i] = new char[width + 1];
		strcpy_s(field_[i], width + 1, read_field[i]);//todo improve
		strcpy_s(field_minus_one_[i], width + 1, read_field[i]);//todo improve
	}
}

char ** GOLField::life(const int generations) const
{
	for(int gen = 0; gen < generations; ++gen)
	{
		for (int i = 0; i < height_; ++i)
		{
			for (int j = 0; j < width_; ++j)
			{
				int neighbors = 0;

				if (field_minus_one_[(i - 1 + height_) % height_][j] == 'x')
				{
					++neighbors;
				}
				if (field_minus_one_[(i + 1 + height_) % height_][j] == 'x')
				{
					++neighbors;
				}
				if (field_minus_one_[i][(j - 1 + width_) % width_] == 'x')
				{
					++neighbors;
				}
				if (field_minus_one_[i][(j + 1 + width_) % width_] == 'x')
				{
					++neighbors;
				}
				if (field_minus_one_[(i - 1 + height_) % height_][(j - 1 + width_) % width_] == 'x')
				{
					++neighbors;
				}
				if (field_minus_one_[(i + 1 + height_) % height_][(j + 1 + width_) % width_] == 'x')
				{
					++neighbors;
				}
				if (field_minus_one_[(i - 1 + height_) % height_][(j + 1 + width_) % width_] == 'x')
				{
					++neighbors;
				}
				if (field_minus_one_[(i + 1 + height_) % height_][(j - 1 + width_) % width_] == 'x')
				{
					++neighbors;
				}

				if (field_minus_one_[i][j] == '.')
				{
					//Birth: A dead cell with exactly three live neighbors becomes a live cell.

					if (neighbors == 3)
					{
						field_[i][j] = 'x';
					}
				}
				else if (field_minus_one_[i][j] == 'x')
				{
					//Survival: A live cell with two or three live neighbors stays alive.
					//Death: A live cell with four or more neighbors dies from overpopulation, with one or none neighbors dies from isolation.
					//-> if not 2 or 3 then die
					if (!(neighbors == 3 || neighbors == 2))
					{
						field_[i][j] = '.';
					}
				}
			}
		}

		for (int a = 0; a < height_; ++a)
		{
			strcpy_s(field_minus_one_[a], width_ + 1, field_[a]);//todo improve
			//std::cout << field_[a] << std::endl;
		}
	}
	return field_;
}

GOLField::~GOLField()
{
	//Free each sub-array
	for (int i = 0; i < height_; ++i) {
		delete[] field_[i];
		delete[] field_minus_one_[i];
	}
	//Free the array of pointers
	delete[] field_;
	delete[] field_minus_one_;
}
