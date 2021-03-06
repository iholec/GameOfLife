// GameOfLife.cpp : Defines the entry point for the console application.
//todo pointer switch, byte array, check if two per inner loop faster, board setting if to one if, au�enkreis extra, einlesen auf einmal mit read size gr��e
#include "stdafx.h"
#include <omp.h>
#include <string>
#include <iostream> 
#include <fstream> 
#include <sstream> 
#include <chrono>
#include <sstream>
#include <iomanip>

#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#define __CL_ENABLE_EXCEPTIONS

#if defined(__APPLE__) || defined(__MACOSX)
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.hpp>
#endif

#pragma comment(lib, "OpenCL.lib")

#define XY_TO_INDEX(X,Y) (((Y) * width) + ( X ))


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
<<<<<<< HEAD
=======
	bool is_sequential = false;
>>>>>>> master

	std::chrono::high_resolution_clock::time_point time_start;
	std::chrono::high_resolution_clock::time_point time_end;
	std::chrono::high_resolution_clock::duration duration;
<<<<<<< HEAD

	bool lookup[2][9] = {
		{ 0,0,0,1,0,0,0,0,0 },
		{ 0,0,1,1,0,0,0,0,0 }
	};

	enum Mode
	{
		seq,
		omp,
		ocl
	};

	enum Device
	{
		none,
		cpu,
		gpu
	};

	Mode mode;
	Device device;

	int threads;
	int deviceId = 0;
	int platformId = 0;
=======
>>>>>>> master

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
<<<<<<< HEAD
			else if (arg == "--measure")
			{
=======
			else if (arg == "--measure") {
>>>>>>> master
				time_measure = true;
			}
			else if (arg == "--mode")
			{
				std::string mode_string(argv[i + 1]);
				if (mode_string == "seq")
				{
<<<<<<< HEAD
					mode = seq;
				}
				else if (mode_string == "omp")
				{
					mode = omp;
				}
				else if (mode_string == "ocl")
				{
					mode = ocl;
=======
					is_sequential = true;
>>>>>>> master
				}
				++i;
			}
			else if (arg == "--threads")
			{
				ss << argv[i + 1];
				ss >> threads;

				ss.str(""); // clear the stringstream
				ss.clear(); // clear the state flags for another conversion
			}
			else if (arg == "--device" && mode == ocl)
			{
				std::string device_string(argv[i + 1]);

				if (device_string == "gpu")
				{
					device = gpu;
				}
				else if (device_string == "cpu")
				{
					device = cpu;
				}
			}
			else if (arg == "--platformId" && mode == ocl)
			{
				ss << argv[i + 1];
				ss >> platformId;

				ss.str(""); // clear the stringstream
				ss.clear(); // clear the state flags for another conversion
			}
			else if (arg == "--deviceId" && mode == ocl)
			{
				ss << argv[i + 1];
				ss >> deviceId;

				ss.str(""); // clear the stringstream
				ss.clear(); // clear the state flags for another conversion
			}
		}

		if (time_measure)
		{
			time_start = std::chrono::high_resolution_clock::now();
		}

		if(time_measure)
		{
			time_start = std::chrono::high_resolution_clock::now();
		}

		//load file 
		if (!load_name.empty())
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

<<<<<<< HEAD
				bool ** bufferdBoard;
				bufferdBoard = new bool*[2];
				bufferdBoard[0] = new bool[height*width];
				bufferdBoard[1] = new bool[height*width];

				bool ** board = new bool *[height + 1];
				bool ** board_minus_one = new bool *[height + 1];

				bool mapSwitch = false;
=======
				char * board = new char [(width * height) + 1];//todo improve, make 1D with  int array[width * height + 1]; int SetElement(int row, int col, int value){ array[width * row + col] = value};
				board[width * height] = '\0';
>>>>>>> master

				for (int i = 0; i < (width * height); i += width)
				{
<<<<<<< HEAD
					board[i] = new bool[width + 1];
					board_minus_one[i] = new bool[width + 1];
					std::getline(gol_file_in, line);

					bool * curr_board = board[i];
					bool * curr_board_minus_one = board_minus_one[i];
					
					for (int x = 0; x < width; ++x)
					{
						curr_board[x] = (line[x] == 'x');
						curr_board_minus_one[x] = (line[x] == 'x');
						
						bufferdBoard[0][XY_TO_INDEX(x, i)] = (line[x] == 'x');
						bufferdBoard[1][XY_TO_INDEX(x, i)] = (line[x] == 'x');

					}
				}
				
				gol_file_in.close();

				//init time
				if (time_measure && mode != ocl)
=======
					std::getline(gol_file_in, line);
					std::memcpy(board + i, line.c_str(), width * sizeof(char));
				}

				//std::cout << board;

				gol_file_in.close();

				//init time
				if (time_measure)
>>>>>>> master
				{
					time_end = std::chrono::high_resolution_clock::now();
					duration = std::chrono::high_resolution_clock::duration(time_end - time_start);
					std::cout << format_time(duration) << "; ";
<<<<<<< HEAD

					time_start = std::chrono::high_resolution_clock::now();
				}

				//compute gol
				if (mode == seq)
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
				else if (mode == omp)
				{
					if (threads > 0) {
						omp_set_dynamic(0);
						omp_set_num_threads(threads);
					}

					for (int gen = 0; gen < generations; ++gen) //todo handle edge cases alone
					{
						# pragma omp parallel
						{
							#pragma omp for
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
							//bool** temp = board;
							//board = board_minus_one;
							//board_minus_one = temp;
							#pragma omp for
							for (int a = 0; a < height; ++a)
							{
								memcpy(board_minus_one[a], board[a], width * sizeof(bool)); //todo pointer swap
							}
						}
					}
				}
				else if (mode == ocl)
				{
					const std::string KERNEL_FILE = "gol_kernel.cl";
					cl_int err = CL_SUCCESS;
					cl::Program program;
					std::vector<cl::Device> devices;

					try
					{
						// get available platforms ( NVIDIA, Intel, AMD,...)
						std::vector<cl::Platform> platforms;
						cl::Platform::get(&platforms);

						if (platforms.empty())
						{
							std::cout << "No OpenCL platforms available!\n";
							return 1;
						}


						if (device == gpu)
						{
							//todo set platform id
							std::string* text = new std::string;
							int i = 0;
							for(cl::Platform platform : platforms)
							{
								platform.getInfo(CL_PLATFORM_VENDOR, text);
								if(text->find("NVIDIA") != std::string::npos)
								{
									platformId = i;
								}
								++i;
							}
							//todo set device id
						}
						else if (device == cpu)
						{
							//todo set platform id
							std::string* text = new std::string;
							int i = 0;
							for (cl::Platform platform : platforms)
							{
								platform.getInfo(CL_PLATFORM_VENDOR, text);
								if (text->find("Intel") != std::string::npos)
								{
									platformId = i;
								}
								++i;
							}
							//todo set device id
						}

						// create a context and get available devices
						cl::Platform platform = platforms[platformId]; // on a different machine, you may have to select a different platform!
						cl_context_properties properties[] = { CL_CONTEXT_PLATFORM, reinterpret_cast<cl_context_properties>((platforms[platformId])()), 0 };

						cl::Context context;

						if (device == gpu)
						{
							context = cl::Context(CL_DEVICE_TYPE_GPU, properties);
						}
						else if (device == cpu)
						{
							context = cl::Context(CL_DEVICE_TYPE_CPU, properties);
						}
						else
						{
							context = cl::Context(CL_DEVICE_TYPE_ALL, properties);
						}

						devices = context.getInfo<CL_CONTEXT_DEVICES>();

						// load and build the kernel
						std::ifstream sourceFile(KERNEL_FILE);
						if (!sourceFile)
						{
							std::cout << "kernel source file " << KERNEL_FILE << " not found!" << std::endl;
							return 1;
						}

						std::string sourceCode(
							std::istreambuf_iterator<char>(sourceFile),
							(std::istreambuf_iterator<char>()));

						cl::Program::Sources source(1, std::make_pair(sourceCode.c_str(), sourceCode.length() + 1));
						program = cl::Program(context, source);
						program.build(devices);

						//create kernels
						cl::Kernel kernel(program, "game_of_life_one_dim", &err);
						cl::Event event;
						// launch kernel
						cl::CommandQueue queue(context, devices[deviceId], 0, &err);

						unsigned int mapSize = width * height;
						
						cl::Buffer in = cl::Buffer(context, CL_MEM_READ_ONLY, sizeof(bool) * mapSize);
						cl::Buffer out = cl::Buffer(context, CL_MEM_WRITE_ONLY, sizeof(bool) * mapSize);

						kernel.setArg(0, in);
						kernel.setArg(1, out);
						kernel.setArg(2, width);
						kernel.setArg(3, height);
						
						cl::NDRange global(mapSize);
						cl::NDRange local(250); //Unterteilung der arbeitspakete

						if (time_measure)
						{
							time_end = std::chrono::high_resolution_clock::now();
							duration = std::chrono::high_resolution_clock::duration(time_end - time_start);
							std::cout << format_time(duration) << "; ";

							time_start = std::chrono::high_resolution_clock::now();
						}

						unsigned int map_byte_size = sizeof(bool) * mapSize;
						
						if(device == gpu)
						{
							for (int gen = 0; gen < generations; ++gen) //todo handle edge cases alone
							{

								queue.enqueueWriteBuffer(in, CL_FALSE, 0, map_byte_size, bufferdBoard[mapSwitch]); // pointer to input

								queue.enqueueNDRangeKernel(kernel, cl::NullRange, global, local);

								queue.enqueueReadBuffer(out, CL_FALSE, 0, map_byte_size, bufferdBoard[!mapSwitch]);

								mapSwitch = !mapSwitch;
							}
						}
						else if (device == cpu)
						{
							for (int gen = 0; gen < generations; ++gen) //todo handle edge cases alone
							{

								queue.enqueueWriteBuffer(in, CL_FALSE, 0, map_byte_size, bufferdBoard[mapSwitch]); // pointer to input

								queue.enqueueNDRangeKernel(kernel, 0, global, cl::NullRange, NULL, &event);

								event.wait();
								
								queue.enqueueReadBuffer(out, CL_FALSE, 0, map_byte_size, bufferdBoard[!mapSwitch]);

								mapSwitch = !mapSwitch;
							}
						}
					}
					catch (cl::Error err)
					{
						// error handling
						// if the kernel has failed to compile, print the error log
						std::string s;
						program.getBuildInfo(devices[deviceId], CL_PROGRAM_BUILD_LOG, &s);
						std::cout << s << std::endl;
						program.getBuildInfo(devices[deviceId], CL_PROGRAM_BUILD_OPTIONS, &s);
						std::cout << s << std::endl;

						std::cerr
							<< "ERROR: "
							<< err.what()
							<< "("
							<< err.err()
							<< ")"
							<< std::endl;
					}

				}
=======

					time_start = std::chrono::high_resolution_clock::now();
				}

				//create and compute gol
				//GOLField* golf = new GOLField(board, width, height);
				//board = golf->life(generations);
>>>>>>> master

				//kernel time
				if (time_measure)
				{
					time_end = std::chrono::high_resolution_clock::now();
					duration = std::chrono::high_resolution_clock::duration(time_end - time_start);
					std::cout << format_time(duration) << "; ";

					time_start = std::chrono::high_resolution_clock::now();
				}

				//write to file

				if(mode == ocl)
				{
					if (!save_name.empty())
					{
						std::ofstream gol_file_out(save_name);
						gol_file_out << width << "," << height << '\n';
						for (int i = 0; i < height; ++i)
						{
							for (int x = 0; x < width; ++x)
							{
								bufferdBoard[mapSwitch][XY_TO_INDEX(x, i)] ? gol_file_out << 'x' : gol_file_out << '.';
							}

							gol_file_out << '\n';
						}

						gol_file_out.close();
					}
				}
				else
				{
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

<<<<<<< HEAD
				delete[] bufferdBoard[0];
				delete[] bufferdBoard[1];

				delete[] bufferdBoard;
=======
				//delete golf;
>>>>>>> master

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


