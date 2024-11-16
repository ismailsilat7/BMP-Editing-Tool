# BMP-Editing-Tool
BMP Image Editing Tool for PF Project @ FAST NU Semester 1

# BMP File Format

The BMP file format is used to store bitmap digital images. Below are the details of the **Bitmap File Header** and **Bitmap Info Header**.

---

## Bitmap File Header

| Offset (hex) | Offset (dec) | Size (bytes) | Purpose                                                                                                                                 |
|--------------|--------------|--------------|-----------------------------------------------------------------------------------------------------------------------------------------|
| 00           | 0            | 2            | The header field used to identify the BMP and DIB file. For BMP, this is `BM` in ASCII, which is `0x42 0x4D` in hexadecimal.            |
| 02           | 2            | 4            | The size of the BMP file in bytes.                                                                                                     |
| 06           | 6            | 2            | Reserved; actual value depends on the application that creates the image. It can be manually set to `0`.                              |
| 08           | 8            | 2            | Reserved; actual value depends on the application that creates the image. It can be manually set to `0`.                              |
| 0A           | 10           | 4            | The offset, i.e., starting address of the byte where the bitmap image data (pixel array) can be found.                                 |

---

## Bitmap Info Header

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

For more details, visit the [BMP file format Wikipedia page](https://en.wikipedia.org/wiki/BMP_file_format).


### Requirements for Standard 24-bit BMP Files

We will be dealing with **standard 24-bit BMP files only**, for which the following checks are required:

| **Header Field**  | **Value for 24-bit BMP** |
|--------------------|--------------------------|
| `bfType`          | `0x4D42` (`BM`)         |
| `bfOffBits`       | `54`                    |
| `biSize`          | `40`                    |
| `biPlanes`        | `1`                     |
| `biBitCount`      | `24`                    |
| `biCompression`   | `0` (BI_RGB)            |

### Explanation of Header Fields:
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

### Note:
These checks ensure that the BMP file conforms to the standard 24-bit uncompressed format. Any deviation from these values will result in an "Unsupported file format" error.

