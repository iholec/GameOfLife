#define XY_TO_INDEX(X,Y) (((Y) * width) + ( X ))

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

//__kernel void game_of_life_two_dim(__global const bool *prev_rows_minus, __global bool *prev_rows, __global const bool *prev_rows_plus, __global bool *boardboard, int width)
__kernel void game_of_life_one_dim(__global const bool *in, __global bool *out, int width, int height)
{
	int j = get_global_id(0);
	int neighbors = 0;

	int y = j / width;
	int x = j - (y * width);

	int line1 = ((y - 1) < 0) ? height - 1 : (y - 1);
	int line3 = ((y + 1) >= height) ? 0 : (y + 1);

	int row1 = ((x - 1) < 0) ? width - 1 : (x - 1);
	int row3 = ((x + 1) >= width) ? 0 : (x + 1);

	neighbors += in[XY_TO_INDEX(row1, line1)];
	neighbors += in[XY_TO_INDEX(x, line1)];
	neighbors += in[XY_TO_INDEX(row3, line1)];
	neighbors += in[XY_TO_INDEX(row1, y)];
	neighbors += in[XY_TO_INDEX(row3, y)];
	neighbors += in[XY_TO_INDEX(row1, line3)];
	neighbors += in[XY_TO_INDEX(x, line3)];
	neighbors += in[XY_TO_INDEX(row3, line3)];

	out[j] = lookup[in[j]][neighbors];
}