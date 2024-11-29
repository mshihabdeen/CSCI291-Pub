#include <stdio.h>
#include <stdlib.h>

#define WIDTH 512
#define HEIGHT 512

// Function to read a PGM image in text format.
// 'pixels' stores the pixel values of the image specified by 'filename'.
int readPGMText(const char *filename, unsigned char *pixels, int width, int height) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        return -1;
    }

    char format[3];
    fscanf(file, "%s", format);
    if (strcmp(format, "P2") != 0) {
        fprintf(stderr, "Invalid PGM format\n");
        fclose(file);
        return -1;
    }

    // Skip comments
    char ch;
    while ((ch = fgetc(file)) == '#') {
        while (fgetc(file) != '\n');
    }
    ungetc(ch, file);

    fscanf(file, "%d %d", &width, &height);
    int maxGray;
    fscanf(file, "%d", &maxGray);

    for (int i = 0; i < width * height; i++) {
        int pixel;
        fscanf(file, "%d", &pixel);
        pixels[i] = (unsigned char)pixel;
    }

    fclose(file);
    return 0;
}

// Function to write a PGM image in text format.
// The dereferenced values of 'pixels' are stored in the PGM image specified by 'filename'.
int writePGMText(const char *filename, unsigned char *pixels, int width, int height) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        return -1;
    }

    fprintf(file, "P2\n");
    fprintf(file, "%d %d\n", width, height);
    fprintf(file, "255\n");

    for (int i = 0; i < width * height; i++) {
        fprintf(file, "%d\n", pixels[i]);
    }

    fclose(file);
    return 0;
}

// Function to write a PGM image in binary format.
// The dereferenced values of 'pixels' are stored in the PGM image specified by 'filename' in binary format.
int writePGMBinary(const char *filename, unsigned char *pixels, int width, int height) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        return -1;
    }

    fprintf(file, "P5\n");
    fprintf(file, "%d %d\n", width, height);
    fprintf(file, "255\n");

    fwrite(pixels, sizeof(unsigned char), width * height, file);

    fclose(file);
    return 0;
}

// Function to hide a secret image using the 4-bit LSB steganography algorithm.
// The dereferenced values of 'coverPixels' (cover image) are updated with the dereferenced values of 
// 'secretPixels' (secret image) based on the 4-bit LSB steganography algorithm
void embedLSB(unsigned char *coverPixels, unsigned char *secretPixels, int width, int height) {
    for (int i = 0; i < width * height; i++) {
        coverPixels[i] = (coverPixels[i] & 0xF0) | ((secretPixels[i] & 0xF0) >> 4);
    }
}

// Function to extract the secret image using 4-LSB steganography algorithm.
// The extracted pixel values, derived from the stego image referenced by 'coverPixels',
// are stored in the memory space pointed to by 'outputPixels' 
void extractLSB(unsigned char *coverPixels, unsigned char *outputPixels, int width, int height) {
    for (int i = 0; i < width * height; i++) {
        outputPixels[i] = (coverPixels[i] & 0x0F) << 4;
    }
}

int main() {
    char cover_image[] = "baboon.pgm";
    char secret_image[] = "farm.pgm";
    char stego_image[] = "stego_image_bin.pgm";
    char extracted_secret[] = "extracted_secret.pgm";

    unsigned char *coverPixels, *secretPixels, *outputPixels;
    int coverWidth = WIDTH, coverHeight = HEIGHT, secretWidth = WIDTH, secretHeight = HEIGHT;

    // Using malloc, dynamically request exact memory space, referenced by coverPixels, to store the cover image pixel values.
    coverPixels = (unsigned char *)malloc(coverWidth * coverHeight * sizeof(unsigned char));
    if (coverPixels == NULL) {
        fprintf(stderr, "Memory allocation failed for coverPixels\n");
        return -1;
    }

    // Read the cover image file (text PGM) and store its pixels in 'coverPixels' referenced memory space.
    if (readPGMText(cover_image, coverPixels, coverWidth, coverHeight) != 0) {
        free(coverPixels);
        return -1;
    }

    // Using malloc, dynamically request exact memory space, referenced by 'secretPixels', to store the secret image pixel values.
    secretPixels = (unsigned char *)malloc(secretWidth * secretHeight * sizeof(unsigned char));
    if (secretPixels == NULL) {
        fprintf(stderr, "Memory allocation failed for secretPixels\n");
        free(coverPixels);
        return -1;
    }

    // Read the secret image file (text PGM) and store its pixels in 'secretPixels' referenced memory space.
    if (readPGMText(secret_image, secretPixels, secretWidth, secretHeight) != 0) {
        free(coverPixels);
        free(secretPixels);
        return -1;
    }

    // Check if the dimensions of both images match, exit if they don't.
    if (coverWidth != secretWidth || coverHeight != secretHeight) {
        fprintf(stderr, "Image dimensions do not match\n");
        free(coverPixels);
        free(secretPixels);
        return -1;
    }

    // Call the function embedLSB to embed the secret image into the cover image.
    embedLSB(coverPixels, secretPixels, coverWidth, coverHeight);

    // Save the stego image into binary format to stego_image_bin.pgm
    if (writePGMBinary(stego_image, coverPixels, coverWidth, coverHeight) != 0) {
        free(coverPixels);
        free(secretPixels);
        return -1;
    }

    // Using malloc, dynamically request exact memory space, referenced by 'outputPixels', to store the extracted secret image
    outputPixels = (unsigned char *)malloc(secretWidth * secretHeight * sizeof(unsigned char));
    if (outputPixels == NULL) {
        fprintf(stderr, "Memory allocation failed for outputPixels\n");
        free(coverPixels);
        free(secretPixels);
        return -1;
    }

    // Call the function extractLSB to extract the secret image from the stego image
    extractLSB(coverPixels, outputPixels, coverWidth, coverHeight);

    // Save the extracted secret image in a text format to extracted_secret.pgm
    if (writePGMText(extracted_secret, outputPixels, secretWidth, secretHeight) != 0) {
        free(coverPixels);
        free(secretPixels);
        free(outputPixels);
        return -1;
    }

    // Free allocated memory
    free(coverPixels);
    free(secretPixels);
    free(outputPixels);

    return 0;
}
