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
			const int i_minus = i - 1 >= 0 ? i - 1 : height_ - 1;
			const int i_plus = i + 1 < height_ ? i + 1 : 0;

			for (int j = 0; j < width_; ++j)
			{
				int neighbors = 0;

				const int j_minus = j - 1 >= 0 ? j - 1 : width_ - 1;
				const int j_plus = j + 1 < width_ ? j + 1 : 0;

				neighbors += field_minus_one_[i_minus][j];
				neighbors += field_minus_one_[i_plus][j];
				neighbors += field_minus_one_[i][j_minus];
				neighbors += field_minus_one_[i][j_plus];
				neighbors += field_minus_one_[i_minus][j_minus];
				neighbors += field_minus_one_[i_plus][j_plus];
				neighbors += field_minus_one_[i_minus][j_plus];
				neighbors += field_minus_one_[i_plus][j_minus];

				if (!field_minus_one_[i][j])
				{
					//Birth: A dead cell with exactly three live neighbors becomes a live cell.
					if (neighbors == 3)
					{
						field_[i][j] = true;
					}
				}
				else
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
