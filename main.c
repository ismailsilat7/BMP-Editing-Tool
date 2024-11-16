#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "filters.h"

int main() {
    
    // taking input for read and write file
    char * infile = "./images/courtyard.bmp";
    char * outfile = "./images/outsample1.bmp";

    // opening readfile
    FILE *readfile = fopen(infile, "rb");
    if (readfile == NULL) {
        printf("File %s not found\n", infile);
        return 1;
    }

    //opening writefile
    FILE *writefile = fopen(outfile, "wb");
    if (writefile == NULL) {
        printf("Couldn't create File %s\n", outfile);
        fclose(readfile);
        return 1;
    }

    // reading bmp image headers from readfile
    BITMAPFILEHEADER fileheader;
    fread(&fileheader, sizeof(BITMAPFILEHEADER), 1, readfile);
    BITMAPINFOHEADER infoheader;
    fread(&infoheader, sizeof(BITMAPINFOHEADER), 1, readfile);

    // dealing with standard 24 bit uncompressed bmp files only so ensuring file meets criteria
    if (fileheader.bfType != 0x4d42 || fileheader.bfOffBits != 54 || infoheader.biSize != 40 || infoheader.biBitCount != 24 || infoheader.biCompression != 0) {
        // 0x4d42 translates to MB, since most significant bit comes in the end, it is actually BM (BitMap), thus we are ensuring the file is a BitMap file
        // bfOffBits is the offsett (starting address) of the byte where pixel array starts, must be 54 = BITMAPFILEHEADER (14 bytes) + BITMAPINFOHEADER (40 bytes) for 24 bit uncompressed
        // Also ensure that infoheader size is 40
        // Bit count must be 24 
        printf("BITMAPFILEHEADER size: %lu\n", sizeof(BITMAPFILEHEADER));
        printf("BITMAPINFOHEADER size: %lu\n", sizeof(BITMAPINFOHEADER));
        printf("fileheader.bfType: %d\nfileheader.bfOffBits: %d\ninfoheader.biSize: %d\ninfoheader.biBitCount: %d\nbiCompression: %d\n", fileheader.bfType,fileheader.bfOffBits,infoheader.biSize, infoheader.biBitCount, infoheader.biCompression);
        printf("File is not a standard 24 bit uncompressed bmp file\n");
        fclose(writefile);
        fclose(readfile);
        return 1;
    }


    int width = infoheader.biWidth; 
    int height = abs(infoheader.biHeight); // can be negative if pixel array is stored top-down instead of the more common bottom-up (The pixel array starts from the bottom row of the image and moves upward to the top) approach.

    // allocating memory to create a 2D array of RGBTRIPLE, This declares pixelArray as a pointer to a 2D array where each row has width elements of type RGBTRIPLE.
    RGBTRIPLE(*pixelArray)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (pixelArray == NULL) {
        printf("Memory allocation failed\n");
        fclose(writefile);
        fclose(readfile);
        return 1;
    }

    // The bits representing the bitmap pixels are packed in rows (also known as strides or scan lines). The size of each row is rounded up to a multiple of 4 bytes (a 32-bit DWORD) by padding which is stored at the end of each row
    // padding shall be ignored when loading data to pixelArray
    int padding = ( 4 - ((width*3) % 4) ) % 4;

    // Reading image pixel data from readfile 
    for (int i = 0; i < height; i++) {
        //reading width * 3 bytes
        fread(pixelArray[i], sizeof(RGBTRIPLE), width, readfile);

        //skip padding ( 4 - ((width*3) % 4) ) % 4 bytes
        fseek(readfile, padding, SEEK_CUR);
    }


    // Call filters!!!! - manipulating pixelArray



    // Writing outfile's headers
    fwrite(&fileheader, sizeof(BITMAPFILEHEADER), 1, writefile);
    fwrite(&infoheader, sizeof(BITMAPINFOHEADER), 1, writefile);

    BYTE paddingValue = 0x00;
    // writing manipulated data to bitmap file
    for (int i = 0; i < height; i++) {
        fwrite(pixelArray[i], sizeof(RGBTRIPLE), width, writefile);
        // writing padding at the end of row
        fwrite(&paddingValue, sizeof(BYTE), padding, writefile);
    }

    fclose(writefile);
    fclose(readfile);
    return 0;
}

