## An efficient imlementation of the Game of Life in C++

# Includes two Versions 

	- ('Abgabe 1'): No Parallelisation
	- ('Abgabe 2'): Parallelisation with OpenCL (CPU and GPU, testet on NVIDIA Graphics Card with Cuda) and OpenMP
	
# Usage

	- --mode seq (select sequential version (Abgabe 1))
	- --mode omp --threads <NUM> (select parallel OpenMP version)
	- --mode ocl (select parallel OpenCL version)
	
	OpenCL specific additional command line parameters:
	
	- --device cpu|gpu (automatically selects platform & device)
	- --platformId NUM (user-defined selection of platform)
	- --deviceId NUM (user-defined selection of device on platform)
