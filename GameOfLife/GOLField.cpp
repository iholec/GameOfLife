#include "stdafx.h"
#include "GOLField.h"
#include <string>
#include <iostream>

GOLField::GOLField(bool ** read_field, const int width, const int height)
{
	field_ = new bool * [height + 1];
	field_minus_one_ = new bool * [height + 1];
	height_ = height;
	width_ = width;

	for (int i = 0; i < height; ++i)
	{
		field_[i] = new bool[width + 1];
		field_minus_one_[i] = new bool[width + 1];
		memcpy(field_[i], read_field[i], width * sizeof(bool));
		memcpy(field_minus_one_[i], read_field[i], width * sizeof(bool));
	}
}

bool ** GOLField::life(const int generations) const
{
	for(int gen = 0; gen < generations; ++gen)
	{
		for (int i = 0; i < height_; ++i)
		{
			for (int j = 0; j < width_; ++j)
			{
				int neighbors = 0;

				neighbors += field_minus_one_[(i - 1 + height_) % height_][j];
				neighbors += field_minus_one_[(i + 1 + height_) % height_][j];
				neighbors += field_minus_one_[i][(j - 1 + width_) % width_];
				neighbors += field_minus_one_[i][(j + 1 + width_) % width_];
				neighbors += field_minus_one_[(i - 1 + height_) % height_][(j - 1 + width_) % width_];
				neighbors += field_minus_one_[(i + 1 + height_) % height_][(j + 1 + width_) % width_];
				neighbors += field_minus_one_[(i - 1 + height_) % height_][(j + 1 + width_) % width_];
				neighbors += field_minus_one_[(i + 1 + height_) % height_][(j - 1 + width_) % width_];

				if (!field_minus_one_[i][j])
				{
					//Birth: A dead cell with exactly three live neighbors becomes a live cell.

					if (neighbors == 3)
					{
						field_[i][j] = true;
					}
				}
				else if (field_minus_one_[i][j])
				{
					//Survival: A live cell with two or three live neighbors stays alive.
					//Death: A live cell with four or more neighbors dies from overpopulation, with one or none neighbors dies from isolation.
					//-> if not 2 or 3 then die
					if (!(neighbors == 3 || neighbors == 2))
					{
						field_[i][j] = false;
					}
				}
			}
		}

		for (int a = 0; a < height_; ++a)
		{
			memcpy(field_minus_one_[a], field_[a], width_ * sizeof(char));
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
