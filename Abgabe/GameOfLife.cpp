// GameOfLife.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <string>
#include <iostream> 
#include <fstream> 
#include <sstream> 
#include <chrono>
#include <sstream>
#include <iomanip>



std::string format_time(std::chrono::high_resolution_clock::duration time) 
{
	std::chrono::hours h = std::chrono::duration_cast<std::chrono::hours>(time);
	time -= h;
	std::chrono::minutes m = std::chrono::duration_cast<std::chrono::minutes>(time);
	time -= m;
	std::chrono::seconds s = std::chrono::duration_cast<std::chrono::seconds>(time);
	time -= s;
	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(time);
	std::stringstream ss;
	ss << std::setfill('0') << std::setw(2) << h.count() << ":" << std::setw(2) << m.count() << ":" << std::setw(2) << s.count() << "." << std::setw(3) << ms.count();
	return ss.str();
}


//width = x, height = y
int main(const int argc, char** argv)
{
	std::string load_name;
	std::string save_name;
	int generations;
	int width;
	int height;

	bool time_measure = false;
	bool is_sequential = false;

	std::chrono::high_resolution_clock::time_point time_start;
	std::chrono::high_resolution_clock::time_point time_end;
	std::chrono::high_resolution_clock::duration duration;

	//read argv
	std::stringstream ss;
	if (argc >= 1)
	{
		for (int i = 0; i < argc; ++i)//argv[i]
		{
			const std::string arg = argv[i];
			if (arg == "--load") {
				load_name = argv[i + 1];
				++i;
			}
			else if (arg == "--generations") 
			{
				ss << argv[i + 1];
				ss >> generations;

				ss.str(""); // clear the stringstream
				ss.clear(); // clear the state flags for another conversion
				++i;
			}
			else if (arg == "--save") 
			{
				save_name = argv[i + 1];
				++i;
			}
			else if (arg == "--measure") 
			{
				time_measure = true;
			}
			else if (arg == "--mode") 
			{
				std::string mode(argv[i + 1]);
				if (mode == "seq")
				{
					is_sequential = true;
				}
				++i;
			}
		}

		if (time_measure)
		{
			time_start = std::chrono::high_resolution_clock::now();
		}

		//load file 
		if(!load_name.empty())
		{
			std::string line;
			std::ifstream gol_file_in(load_name);
			if (gol_file_in.is_open())
			{
				std::getline(gol_file_in, line);
				ss << line; 
				std::string integer;
				std::getline(ss, integer, ',');
				ss >> height;
				std::getline(ss, integer, ',');

				ss.str(""); // clear the stringstream
				ss.clear(); // clear the state flags for another conversion

				ss << integer;
				ss >> width;

				ss.str(""); // clear the stringstream
				ss.clear(); // clear the state flags for another conversion

				bool ** board = new bool * [height + 1];
				bool ** board_minus_one = new bool *[height + 1];

				for (int i = 0; i < height; ++i)
				{
					board[i] = new bool[width + 1];
					board_minus_one[i] = new bool[width + 1];
					std::getline(gol_file_in, line);

					bool * curr_board = board[i];
					bool * curr_board_minus_one = board_minus_one[i];

					for(int x = 0; x < width; ++x)
					{
						curr_board[x] = (line[x] == 'x');
						curr_board_minus_one[x] = (line[x] == 'x');

					}
					//std::cout << line << '\n';
				}

				gol_file_in.close();

				//init time
				if (time_measure)
				{
					time_end = std::chrono::high_resolution_clock::now();
					duration = std::chrono::high_resolution_clock::duration(time_end - time_start);
					std::cout << format_time(duration) << "; ";

					time_start = std::chrono::high_resolution_clock::now();
				}

				//compute gol
				for (int gen = 0; gen < generations; ++gen)
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

							if (!prev_rows[j])
							{
								//Birth: A dead cell with exactly three live neighbors becomes a live cell.
								if (neighbors == 3)
								{
									board[i][j] = true;
								}
							}
							else
							{
								//Survival: A live cell with two or three live neighbors stays alive.
								//Death: A live cell with four or more neighbors dies from overpopulation, with one or none neighbors dies from isolation.
								//-> if not 2 or 3 then die
								if (!(neighbors == 3 || neighbors == 2))
								{
									board[i][j] = false;
								}
							}
						}
					}

					for (int a = 0; a < height; ++a)
					{
						memcpy(board_minus_one[a], board[a], width * sizeof(bool));
					}
				}

				//kernel time
				if (time_measure)
				{
					time_end = std::chrono::high_resolution_clock::now();
					duration = std::chrono::high_resolution_clock::duration(time_end - time_start);
					std::cout << format_time(duration) << "; ";

					time_start = std::chrono::high_resolution_clock::now();
				}
				
				//write to file
				if (!save_name.empty())
				{
					std::ofstream gol_file_out(save_name);
					gol_file_out << width << "," << height << '\n';
					for (int i = 0; i < height; ++i)
					{
						bool * curr_board = board[i];
						for (int x = 0; x < width; ++x)
						{
							curr_board[x] ? gol_file_out << 'x' : gol_file_out << '.';
						}

						gol_file_out << '\n';
					}

					gol_file_out.close();
				}

				//delete it all
				//Free each sub-array
				for (int i = 0; i < height; ++i) {
					delete[] board[i];
					delete[] board_minus_one[i];
				}
				//Free the array of pointers
				delete[] board;
				delete[] board_minus_one;

				//finalize time
				if (time_measure)
				{
					time_end = std::chrono::high_resolution_clock::now();
					duration = std::chrono::high_resolution_clock::duration(time_end - time_start);
					std::cout << format_time(duration);
				}
			}

			else std::cout << "Unable to open file";

		}
	}

    return 0;
}


