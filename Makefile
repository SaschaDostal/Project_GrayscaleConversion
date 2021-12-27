CC=gcc

unoptimized:
	$(CC) -o unoptimized.exe unoptimized.c

simd:
	$(CC) -o simd_128.exe simd_128.c -march=native

simd256:
	$(CC) -o simd_256.exe simd_256.c -march=native

openmp:
	$(CC) -fopenmp -o openmp.exe openmp.c
