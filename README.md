# HPC_Project

Project work in the subject "High Performance Computing" from Sascha Dostal and Marc Boehmer.

## Grayscale conversion implementations

There are 6 different implementations of the grayscale conversion:

1. [unoptimised](./unoptimized.c): An unoptimized implementation (the basis for this project).  
2. [simd_128](./simd_128.c): A SIMD implementation using SSE Instructions.  
3. [simd_256](./simd_256.c): A SIMD implementation using AVX Instructions (old version, not completely optimized).  
4. [openmp](./openmp.c): An OpenMP implementation.  
5. [openmp_simd](./openmp_simd.c): A combination of the OpenMP and SIMD SSE implementation (final optimization result).  
6. [opencv](./opencv.cpp): A simple OpenCV C++ implementation for comparison.

## Compilation

All C files can be compiled with the [Makefile](./Makefile).  
The C++ OpenCV implementation can only be compiled with the necessary OpenCV imports/libraries.  

## Benchmarks

The processor setup and the benchmark results can be found in the [Benchmark](./Benchmarks.md) file.  
