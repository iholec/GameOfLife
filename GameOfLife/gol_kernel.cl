__constant bool lookup[2][9] = {
		{ 0,0,0,1,0,0,0,0,0 },
		{ 0,0,1,1,0,0,0,0,0 }
};

//__kernel void game_of_life_one_dim(__global const bool *board, __global bool *board_minus_one, int len, int width, int generations)
//{
//	for (int gen = width; gen < generations - width; ++gen)
//	{
//		for (int i = 0; i < len; ++i)
//		{
//			int neighbors = 0;
//
//			neighbors += board_minus_one[i - 1];
//			neighbors += board_minus_one[i + 1];
//			neighbors += board_minus_one[i - width];
//			neighbors += board_minus_one[i + width];
//			neighbors += board_minus_one[i - width - 1];
//			neighbors += board_minus_one[i - width + 1];
//			neighbors += board_minus_one[i + width - 1];
//			neighbors += board_minus_one[i + width + 1];
//
//
//			//board[i] = lookup[board[i]][neighbors];
//		}
//
//		for (int i = 1; i < width; ++i)//oben ist unten
//		{
//			int neighbors = 0;
//
//
//			//board[i] = lookup[board[i]][neighbors];
//		}
//
//		for (int i = len - width; i < len - 2; ++i)//unten ist oben
//		{
//			int neighbors = 0;
//
//			neighbors += board_minus_one[i - 1];
//			neighbors += board_minus_one[i + 1];
//			neighbors += board_minus_one[i - width];
//			neighbors += board_minus_one[i + width];
//			neighbors += board_minus_one[i - width - 1];
//			neighbors += board_minus_one[i - width + 1];
//			neighbors += board_minus_one[i + width - 1];
//			neighbors += board_minus_one[i + width + 1];
//
//
//			//board[i] = lookup[board[i]][neighbors];
//		}
//
//		//same for first element, links ist letztes
//
//		//same for last element
//
//
//		//std::memcpy(board_minus_one, board, len * sizeof(bool));
//	}
//}

__kernel void game_of_life_two_dim(__global const bool *prev_rows_minus, __global bool *prev_rows, __global const bool *prev_rows_plus, __global bool *boardboard, int width)
{
	int j = get_global_id(0);
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

	boardboard[j] = lookup[boardboard[j]][neighbors];

}