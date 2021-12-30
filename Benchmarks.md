# Benchmarks

## Processor / Compiler Version

A - Ryzen 5600x / GCC 11.2.0
B - Ryzen 3600x / GCC 9.3.0

Benchmark with compiler optimization enabled (-O3).

## Picture

All Benchmarks were carried out with [BenchmarkPictureL.jpg](https://drive.google.com/file/d/1VS0r1vs5GeAXDvkbd77-Uifat9tqF65I/view?usp=sharing).  

Picture Size: w: 15360, h: 8640, 19,6 MB  

## Tables

UNOPTIMIZED | A  | B | Comment
-------- | -------- | -------- | --------
V0   | 0.653950   | 1.6574604   | initial unoptimized version

SIMD | A  | B | Comment
-------- | -------- | -------- | --------
V0 128   | 0.478735   | 0.539196   | SSE Version with approximation shifts and optimized for loop
V0 256   | 0.477895   | 0.541910   | AVX Version with approximation shifts and optimized for loop. Bug: picture fragments
V1 128   | 0.053968   | 0.068251  | SSE Version without conversion to float and more intrinsics

OPENMP | A  | B | Comment
-------- | -------- | -------- | --------
V0   | 0.035776   | 0.038935   | simple omp parallel for
V0   | 0.035529   | 0.033429   | simple omp parallel for simd
V1 fixed threads  | 0.058296   | 0.048471   | omp parallel for with 6 threads
V1 fixed threads  | 0.047874   | 0.040652  | omp parallel for with 8 threads
V1 fixed threads  | 0.040682   | 0.037117  | omp parallel for with 10 threads
V1 fixed threads  | 0.035673   | 0.039915  | omp parallel for with 12 threads
V1 fixed threads  | 0.035734   | 0.043467   | omp parallel for with 24 threads

OPENMP + SIMD | A  | B | Comment
-------- | -------- | -------- | --------
V0 | 0.024145   | 0.027906   | with 6 threads
V0 | 0.022888   | 0.027455   | with 8 threads
V0 | 0.022757   | 0.027640   | with 10 threads
V0 | 0.021817   | 0.028320   | with 12 threads
V0 | 0.022019   | 0.026110  | with 24 threads

OPENCV (C++) | A  | B | Comment
-------- | -------- | -------- | --------
V0 |    |    |

(all values in seconds)
