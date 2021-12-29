#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <immintrin.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// V1
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

    struct timeval start;
    gettimeofday(&start, 0);

    for(int i=0;i<width * height * 3; i+=24) {

        // Load and shuffle data

        __m128i first16byte = _mm_loadu_si128((__m128i*)(img + i));
        __m128i second16byte = _mm_loadu_si128((__m128i*)(img + i + 16));
        __m128i second16byte_aligned = _mm_alignr_epi8(second16byte, first16byte, 12);

        const __m128i shuffle = _mm_set_epi8( 9, 6, 3, 0, 11, 8, 5, 2, 10, 7, 4, 1, 9, 6, 3, 0);
        __m128i rgb_pixel_0123 = _mm_shuffle_epi8(first16byte, shuffle);
        __m128i rgb_pixel_4567 = _mm_shuffle_epi8(second16byte_aligned, shuffle);

        // Sort data by color and shift

        __m128i r_pixel = _mm_alignr_epi8(rgb_pixel_4567, rgb_pixel_0123, 12);
        r_pixel = _mm_srli_epi64(r_pixel, 2);
        r_pixel = _mm_and_si128(r_pixel , _mm_set1_epi8(0b00111111));

        __m128i g_pixel_0123 = _mm_slli_si128(rgb_pixel_0123, 8);
        __m128i g_pixel_4567 = _mm_srli_si128(rgb_pixel_4567, 4);
        __m128i g_pixel = _mm_alignr_epi8(g_pixel_4567, g_pixel_0123, 12);
        g_pixel = _mm_srli_epi64(g_pixel, 1);
        g_pixel = _mm_and_si128(g_pixel , _mm_set1_epi8(0b01111111));

        __m128i b_pixel_0123 = _mm_slli_si128(rgb_pixel_0123, 4);
        __m128i b_pixel_4567 = _mm_srli_si128(rgb_pixel_4567, 8);
        __m128i b_pixel = _mm_alignr_epi8(b_pixel_4567, b_pixel_0123, 12);
        b_pixel = _mm_srli_epi64(b_pixel, 2);
        b_pixel = _mm_and_si128(b_pixel , _mm_set1_epi8(0b00111111));

        // Calculation
        g_pixel = _mm_add_epi64(r_pixel, g_pixel);
        g_pixel = _mm_add_epi64(b_pixel, g_pixel);
        
        _mm_storeu_si128((__m128i *)&gray[i/3], g_pixel);
    }

    struct timeval end;
    gettimeofday(&end, 0);
    long lsec = end.tv_sec - start.tv_sec;
    long lusec = end.tv_usec - start.tv_usec;
    double sec = (lsec + lusec / 1000000.0);
    printf("%8.6f seconds\n", sec);

    stbi_write_jpg("grayscale_simd_128.jpg", width, height, 1, gray, 95);
}
