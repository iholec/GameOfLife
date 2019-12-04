__constant	bool lookup[2][9] = {
		{ 0,0,0,1,0,0,0,0,0 },
		{ 0,0,1,1,0,0,0,0,0 }
};

__kernel void game_of_life(__global const bool *board, __global bool *board_minus_one, int width, int height, int generations)
{
	for (int gen = 0; gen < generations; ++gen) //todo handle edge cases alone
	{
		for (int i = 0; i < height; ++i)
		{
			const int i_minus = i - 1 >= 0 ? i - 1 : height - 1;
			const int i_plus = i + 1 < height ? i + 1 : 0;

			bool * prev_rows_minus = board_minus_one[i_minus];
			bool * prev_rows = board_minus_one[i];
			bool * prev_rows_plus = board_minus_one[i_plus];

			for (int j = 0; j < width; ++j)
			{
				int neighbors = 0;

				const int j_minus = j - 1 >= 0 ? j - 1 : width - 1;
				const int j_plus = j + 1 < width ? j + 1 : 0;

				neighbors += prev_rows_minus[j];
				neighbors += prev_rows_plus[j];
				neighbors += prev_rows[j_minus];
				neighbors += prev_rows[j_plus];
				neighbors += prev_rows_minus[j_minus];
				neighbors += prev_rows_plus[j_plus];
				neighbors += prev_rows_minus[j_plus];
				neighbors += prev_rows_plus[j_minus];

				board[i][j] = lookup[board[i][j]][neighbors];
			}
		}

		for (int a = 0; a < height; ++a)
		{
			memcpy(board_minus_one[a], board[a], width * sizeof(bool)); //todo pointer swap
		}
	}
}