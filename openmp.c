#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define THREADS 24

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

    struct timeval start;
    gettimeofday(&start, 0);

    int pixel_per_thread = (width*height)/THREADS;
    #pragma omp parallel for //simd
    for(int thread = 0; thread < THREADS; thread++){
        for(int x=pixel_per_thread*thread;x<pixel_per_thread*thread+pixel_per_thread;x++) {
            gray[x] =  0.2126 * img[x * 3]
                    + 0.7152 * img[x * 3 + 1] 
                    + 0.0722 * img[x * 3 + 2];
        }
    }

    struct timeval end;
    gettimeofday(&end, 0);
    long lsec = end.tv_sec - start.tv_sec;
    long lusec = end.tv_usec - start.tv_usec;
    double sec = (lsec + lusec / 1000000.0);
    printf("%8.6f seconds\n", sec);

    stbi_write_jpg("grayscale_openmp.jpg", width, height, 1, gray, 95);
}