#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <immintrin.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// V0
int main()
{

    int width, height, channels;
    unsigned char *img = stbi_load("BenchmarkPictureL.jpg", &width, &height, &channels, 0);
    if (img == NULL)
    {
        printf("Err: loading image\n");
        exit(1);
    }

    printf("w: %d ; h: %d ; c: %d\n", width, height, channels);
    
    unsigned char *gray = malloc(width * height);

    //[ r, g, b, r, g, b, ...]
    float* r = malloc(sizeof(float) * width * height);
    float* g = malloc(sizeof(float) * width * height);
    float* b = malloc(sizeof(float) * width * height);

    struct timeval start;
    gettimeofday(&start, 0);

    for(int x=0;x<width*height;x++) {
        r[x] = img[x * 3] >> 2;
        g[x] = img[x * 3 + 1] >> 1;
        b[x] = img[x * 3 + 2] >> 2;
    }

    for(int i=0;i<width * height;i+=8) {
        __m256 rvec = _mm256_loadu_ps(r);
        __m256 gvec = _mm256_loadu_ps(g);
        __m256 bvec = _mm256_loadu_ps(b);
        __m256 sum = _mm256_add_ps (rvec, gvec);
        sum = _mm256_add_ps (bvec, sum);
        
        __m256i int_sum = _mm256_cvtps_epi32(sum);
        int_sum = _mm256_packus_epi32(int_sum, int_sum);
        int_sum = _mm256_packus_epi16(int_sum, int_sum);
        _mm256_storeu_si256((__m256i *)&gray[i], int_sum);

        r += 8;
        g += 8;
        b += 8;
    }

    struct timeval end;
    gettimeofday(&end, 0);
    long lsec = end.tv_sec - start.tv_sec;
    long lusec = end.tv_usec - start.tv_usec;
    double sec = (lsec + lusec / 1000000.0);
    printf("%8.6f seconds\n", sec);

    stbi_write_jpg("grayscale_simd_256.jpg", width, height, 1, gray, 95);
}