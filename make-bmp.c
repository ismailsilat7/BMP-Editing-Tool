#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main() {
    FILE *f = fopen("./images/100x100_image.bmp", "wb");
    if (!f) {
        printf("Error opening file!\n");
        return 1;
    }

    int width = 100;
    int height = 100;

    BITMAPFILEHEADER bfHeader;
    BITMAPINFOHEADER biHeader;

    // Set the bitmap file header
    bfHeader.bfType = 0x4D42;  // 'BM' in little-endian (hexadecimal representation of 'BM')
    bfHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + height * width * sizeof(RGBTRIPLE); // 100x100 image, 3 bytes per pixel
    bfHeader.bfReserved1 = 0;
    bfHeader.bfReserved2 = 0;
    bfHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // Set the bitmap info header
    biHeader.biSize = sizeof(BITMAPINFOHEADER);
    biHeader.biWidth = width;
    biHeader.biHeight = height;
    biHeader.biPlanes = 1;
    biHeader.biBitCount = 24; // 24 bits per pixel (RGB)
    biHeader.biCompression = 0; // No compression
    biHeader.biSizeImage = height * width * sizeof(RGBTRIPLE); // 100x100 image, 3 bytes per pixel
    biHeader.biXPelsPerMeter = 2835; // 72 DPI
    biHeader.biYPelsPerMeter = 2835; // 72 DPI
    biHeader.biClrUsed = 0;
    biHeader.biClrImportant = 0;

    // Write headers to file
    fwrite(&bfHeader, sizeof(BITMAPFILEHEADER), 1, f);
    fwrite(&biHeader, sizeof(BITMAPINFOHEADER), 1, f);

    // Write pixel data (100x100 image with RGB values)
    RGBTRIPLE pixels[100][100];

    // Generate some pattern for the pixels (e.g., alternating colors)
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            pixels[i][j].rgbtRed = (i + j) % 255;
            pixels[i][j].rgbtGreen = (i * j) % 255;
            pixels[i][j].rgbtBlue = (i - j) % 255;
        }
    }

    // Write pixel data (BMP format stores pixels from bottom to top)
    for (int i = height - 1; i >= 0; i--) {
        for (int j = 0; j < width; j++) {
            fwrite(&pixels[i][j], sizeof(RGBTRIPLE), 1, f);
        }
    }

    fclose(f);

    printf("100x100 BMP image created successfully!\n");

    return 0;
}

