# BMP-Editing-Tool
BMP Image Editing Tool for PF Project @ FAST NU Semester 1

## Table of Contents
1. [Introduction](#introduction)  
2. [BMP File Format](#bmp-file-format)  
   - [What is a BMP File?](#what-is-a-bmp-file)  
   - [Structure of a BMP File](#structure-of-a-bmp-file)  
   - [Supported BMP Type](#supported-bmp-type)  
3. [File Structure](#file-structure) 
4. [Function Descriptions](#function-descriptions)
5. [Setup and Usage](#setup-and-usage)
6. [Collaborators](#collaborators)
  

## Introduction

The **BMP Image Editing Tool** is a C-based application developed as part of the **Programming Fundamentals** project for the first semester at **FAST NUCES**. The tool allows users to apply a variety of image processing functions to **24-bit BMP files**. These functions include **grayscale conversion**, **sepia tone application**, **brightness and contrast adjustments**, **image rotation**, and more. The tool is designed to be easy to use with a simple command-line interface, providing essential editing features for BMP images in a lightweight manner.

This project serves as a practical application of core programming concepts such as **file handling**, **looping**, **image processing algorithms**, **pointers** and **array handling** using C. It is structured to help users better understand BMP file formats and image manipulation techniques.


## BMP File Format

The BMP file format is used to store bitmap digital images. Below are the details of the **Bitmap File Header** and **Bitmap Info Header**.

---

### What is a BMP File?

A BMP (Bitmap) file is a raster graphics image file format used to store bitmap digital images, particularly on Windows systems. It contains data organized in a specific structure, including headers and pixel data, to represent an image.

---

### Structure of a BMP File

#### Bitmap File Header

| Offset (hex) | Offset (dec) | Size (bytes) | Purpose                                                                                                                                 |
|--------------|--------------|--------------|-----------------------------------------------------------------------------------------------------------------------------------------|
| 00           | 0            | 2            | The header field used to identify the BMP and DIB file. For BMP, this is `BM` in ASCII, which is `0x42 0x4D` in hexadecimal.            |
| 02           | 2            | 4            | The size of the BMP file in bytes.                                                                                                     |
| 06           | 6            | 2            | Reserved; actual value depends on the application that creates the image. It can be manually set to `0`.                              |
| 08           | 8            | 2            | Reserved; actual value depends on the application that creates the image. It can be manually set to `0`.                              |
| 0A           | 10           | 4            | The offset, i.e., starting address of the byte where the bitmap image data (pixel array) can be found.                                 |

---

#### Bitmap Info Header

| Offset (hex) | Offset (dec) | Size (bytes) | Windows BITMAPINFOHEADER                                                                                                               |
|--------------|--------------|--------------|-----------------------------------------------------------------------------------------------------------------------------------------|
| 0E           | 14           | 4            | The size of this header, in bytes (40).                                                                                                |
| 12           | 18           | 4            | The bitmap width in pixels (signed integer).                                                                                           |
| 16           | 22           | 4            | The bitmap height in pixels (signed integer).                                                                                          |
| 1A           | 26           | 2            | The number of color planes (must be 1).                                                                                                |
| 1C           | 28           | 2            | The number of bits per pixel, which is the color depth of the image. Typical values are `1`, `4`, `8`, `16`, `24`, and `32`.           |
| 1E           | 30           | 4            | The compression method being used.                                                                                                     |
| 22           | 34           | 4            | The image size. This is the size of the raw bitmap data; a dummy `0` can be given for BI_RGB bitmaps.                                   |
| 26           | 38           | 4            | The horizontal resolution of the image in pixels per meter (signed integer).                                                           |
| 2A           | 42           | 4            | The vertical resolution of the image in pixels per meter (signed integer).                                                             |
| 2E           | 46           | 4            | The number of colors in the color palette, or `0` to default to `2^n`.                                                                 |
| 32           | 50           | 4            | The number of important colors used, or `0` when every color is important. Generally ignored.                                          |

---

### Supported BMP Type

We will be dealing with **standard 24-bit BMP files only**, for which the following checks are required:

| **Header Field**  | **Value for 24-bit BMP** |
|--------------------|--------------------------|
| `bfType`          | `0x4D42` (`BM`)         |
| `bfOffBits`       | `54`                    |
| `biSize`          | `40`                    |
| `biPlanes`        | `1`                     |
| `biBitCount`      | `24`                    |
| `biCompression`   | `0` (BI_RGB)            |

---

### Explanation of Header Fields

1. **`bfType`:**  
   Ensures the file is a valid BMP. The ASCII characters `BM` (hex: `0x4D42`) signify this.

2. **`bfOffBits`:**  
   Specifies the starting address of the pixel data. For 24-bit BMPs, this is always `54`.

3. **`biSize`:**  
   Indicates the size of the `BITMAPINFOHEADER`. For standard BMPs, this value is `40`.

4. **`biPlanes`:**  
   Always `1` for BMP files, as only a single color plane is used.

5. **`biBitCount`:**  
   Defines the color depth. A value of `24` means each pixel uses 24 bits (8 bits for each of Red, Green, and Blue channels).

6. **`biCompression`:**  
   Specifies the compression method. A value of `0` (`BI_RGB`) means the image is uncompressed.

---

### Note

These checks ensure that the BMP file conforms to the standard 24-bit uncompressed format. Any deviation from these values will result in an "Unsupported file format" error.
- [Learn more about how are 24-bit BMP Files stored](https://education.siggraph.org/static/HyperVis/asp_data/compimag/bmpfile.htm)

# File Structure

The project is organized as follows:

## Description

- **`images/`**: Folder containing sample BMP images for testing.
  - Includes BMP files such as `100x100_image.bmp`, `stadium.bmp`, etc.
  
- **`bmp.h`**: Header file for defining BMP structures and constants.

- **`filters.c`**: Contains implementations of image processing functions (e.g., grayscale, invert, etc.).

- **`filters.h`**: Header file for declaring image processing functions.

- **`main.c`**: The main program file that drives the tool.

- **`main.exe`**: Compiled executable for the BMP Editing Tool.

- **`make-bmp.c`**: Utility program to generate BMP files for testing.

- **`README.md`**: Documentation file explaining the project, usage, and file details.

# Function Descriptions

## Grayscale
- **Description**: Converts an image to grayscale.
- **How it works**:
  - For each pixel, the red, green, and blue values are summed and averaged.
  - The average value is assigned to the red, green, and blue channels of the pixel.

---

## Sepia
- **Description**: Applies a sepia tone to the image.
- **How it works**:
  - For each pixel, calculates `sepiaRed`, `sepiaGreen`, and `sepiaBlue` values using a predefined formula.
  - Assigns these values to the red, green, and blue channels of the pixel.
- **Reference**: [How is a sepia tone created?](https://stackoverflow.com/questions/1061093/how-is-a-sepia-tone-created)

---

## Reflect
- **Description**: Horizontally reflects the image.
- **How it works**:
  - Divides the image width into two halves.
  - Swaps pixel values from one end to the other.

---

## Blur
- **Description**: Blurs the image.
- **How it works**:
  - For each pixel, calculates the sum of the RGB values of all surrounding pixels.
  - Assigns the mean of these values to the RGB channels of the pixel.

---

## Edges
- **Description**: Detects edges in the image.
- **How it works**:
  - Uses 3x3 Sobel kernels `Gx` and `Gy` to detect changes in pixel values relative to the center pixel.
  - Edge pixels are highlighted in white.
  
---

## Adjust Brightness
- **Description**: Adjusts the brightness of the image.
- **How it works**:
  - Takes a brightness value from the user.
  - Adds this value to the red, green, and blue channels of each pixel.

---

## Adjust Contrast
- **Description**: Adjusts the contrast of the image.
- **How it works**:
  - Takes a `contrast_factor` from the user.
  - Adjusts each pixel value using the formula:  
    `new_value = factor(value - 128) + 128`
- **Reference**: [Contrast Adjustment Algorithm](https://www.dfstudios.co.uk/articles/programming/image-programming-algorithms/image-processing-algorithms-part-5-contrast-adjustment/)

---

## Invert Colors
- **Description**: Inverts the colors of the image.
- **How it works**:
  - For each pixel, subtracts the RGB values from `255` to compute the inverted color.

---

## Pixelate
- **Description**: Applies a pixelation effect to the image.
- **How it works**:
  - Divides the image into blocks of a user-specified size.
  - Assigns the same average RGB value to all pixels in a block.

---

## Vignette
- **Description**: Adds a vignette effect to the image.
- **How it works**:
  - Calculates the distance of each pixel from the center.
  - Based on the ratio of `distance / max_distance`, adjusts the RGB values to darken the edges.

---

## Sharpen
- **Description**: Sharpens the image.
- **How it works**:
  - Applies a 3x3 kernel to each pixel to enhance edges and details.
- **Reference**: [Image Processing Kernels](https://en.wikipedia.org/wiki/Kernel_(image_processing))

---

## Gaussian Blur
- **Description**: Applies a Gaussian blur to the image.
- **How it works**:
  - Uses a 5x5 Gaussian kernel to calculate new pixel values.
- **Reference**: [Gaussian Kernel](https://en.wikipedia.org/wiki/Kernel_(image_processing))

---

## Emboss
- **Description**: Adds an emboss effect to the image.
- **How it works**:
  - Uses a 3x3 kernel to calculate new pixel values based on neighboring pixels.

---

## Rotate 90
- **Description**: Rotates the image 90 degrees clockwise.
- **Note**: Only supports square images currently.

---

## Rotate 180
- **Description**: Rotates the image 180 degrees clockwise.

---

## Rotate 270
- **Description**: Rotates the image 270 degrees clockwise.
- **Note**: Only supports square images currently.

---

## Add Border
- **Description**: Adds a solid-colored border to the image.
- **How it works**:
  - Takes `border_width` and a color as input from the user.
  - Adds the specified border to the image.

## Setup and Usage

### Requirements
To run the BMP Image Editing Tool, you need:
- A **C compiler** (e.g., GCC).  
  - For Windows, you can use MinGW to install GCC.  

### Usage
1. Open your terminal or command prompt.
2. Navigate to the folder containing the source files.
3. Compile the program with the following command:
   - gcc -o main main.c filters.c
4. Run the program:
   - ./main
