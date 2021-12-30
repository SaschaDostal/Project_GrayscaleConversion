CC=gcc

unoptimized:
	$(CC) -O3 -o unoptimized.exe unoptimized.c

simd:
	$(CC) -O3 -o simd_128.exe simd_128.c -march=native

simd256:
	$(CC) -O3 -o simd_256.exe simd_256.c -march=native

openmp:
	$(CC) -O3 -fopenmp -o openmp.exe openmp.c

openmpsimd:
	$(CC) -O3 -fopenmp -o openmp_simd.exe openmp_simd.c -march=native
