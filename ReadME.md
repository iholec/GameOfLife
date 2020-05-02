## An efficient imlementation of the Game of Life in C++
	
# Usage

	- --load NAME (where NAME is a filename with the extension ’.gol’)
	- Number of generations to compute: --generations NUM (where NUM is a number).
	- Save a computation: --save NAME (where NAME is a filename with the extension ’.gol’)
	- Perform measurement: --measure (generates measurement output on stdout)
	- --mode seq (select sequential version)
	- --mode omp --threads <NUM> (select parallel OpenMP version)
	- --mode ocl (select parallel OpenCL version)
	
	OpenCL specific additional command line parameters:
	
	- --device cpu|gpu (automatically selects platform & device)
	- --platformId NUM (user-defined selection of platform)
	- --deviceId NUM (user-defined selection of device on platform)
