#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

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

    struct timeval start;
    gettimeofday(&start, 0);

    for(int x=0;x<width;x++) {
        for(int y=0;y<height;y++) {
            gray[y * width + x] =  0.2126 * img[(y * width + x) * 3]
                                 + 0.7152 * img[(y * width + x) * 3 + 1] 
                                 + 0.0722 * img[(y * width + x) * 3 + 2];
        }
    }

    struct timeval end;
    gettimeofday(&end, 0);
    long lsec = end.tv_sec - start.tv_sec;
    long lusec = end.tv_usec - start.tv_usec;
    double sec = (lsec + lusec / 1000000.0);
    printf("%8.6f seconds\n", sec);

    stbi_write_jpg("grayscale_unoptimized.jpg", width, height, 1, gray, 95);
}