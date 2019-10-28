// GameOfLife.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <string>
#include <iostream> 
#include <fstream> 
#include <sstream> 
#include <chrono>
#include <sstream>
#include <iomanip>
#include "GOLField.h"



std::string format_time(std::chrono::high_resolution_clock::duration time) {
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
int main(int argc, char** argv)
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
			else if (arg == "--generations") {
				ss << argv[i + 1];
				ss >> generations;

				ss.str(""); // clear the stringstream
				ss.clear(); // clear the state flags for another conversion
				++i;
			}
			else if (arg == "--save") {
				save_name = argv[i + 1];
				++i;
			}
			else if (arg == "--measure") {
				time_measure = true;
			}
			else if (arg == "--mode") {
				std::string mode(argv[i + 1]);
				if (mode == "seq")
				{
					is_sequential = true;
				}
				++i;
			}
		}

		if(time_measure)
		{
			time_start = std::chrono::high_resolution_clock::now();
		}

		//load file 
		if(!load_name.empty())//todo testen ob problem macht
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

				char * board = new char [(width * height) + 1];//todo improve, make 1D with  int array[width * height + 1]; int SetElement(int row, int col, int value){ array[width * row + col] = value};
				board[width * height] = '\0';

				for (int i = 0; i < (width * height); i += width)
				{
					std::getline(gol_file_in, line);
					std::memcpy(board + i, line.c_str(), width * sizeof(char));
				}

				//std::cout << board;

				gol_file_in.close();

				//init time
				if (time_measure)
				{
					time_end = std::chrono::high_resolution_clock::now();
					duration = std::chrono::high_resolution_clock::duration(time_end - time_start);
					std::cout << format_time(duration) << "; ";

					time_start = std::chrono::high_resolution_clock::now();
				}

				//create and compute gol
				//GOLField* golf = new GOLField(board, width, height);
				//board = golf->life(generations);

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
					for (int i = 0; i < height; ++i)
					{
						gol_file_out << board[i] << '\n';
					}

					gol_file_out.close();
				}

				//delete golf;

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


