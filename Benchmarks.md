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

OPENMP | A  | B | Comment
-------- | -------- | -------- | --------
V0   | 0.035776   | 0.038935   | simple omp parallel for

(all values in seconds)
