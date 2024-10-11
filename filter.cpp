#include "filter.h"
#include "helpers.h"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>

// TODO - Implement the filter function
int filterImage(const char *infile, const char *outfile, const char *filterType) {
    // DEBUG - PRINT FILTERTYPE
    printf("Filter Type: %s\n", filterType);

	// Open input file
	FILE *inptr = fopen(infile, "r");

	if (inptr == NULL) {
		printf("Could not open %s.\n", infile);
		return -1;
	}

	// Check if output file already exists. if it does, create a new outfile name with a number appended,
	// Make this iterative until a unique name is found
	FILE *outptr = fopen(outfile, "r");
	std::string newOutFile = outfile;

	if (outptr != NULL) {
		fclose(outptr);

		// loop until "Filename (n)" is NULL
		int fileCount = 1;
		while (true) {
            if (fileCount == 1) {
                newOutFile.insert(newOutFile.find_last_of('.'), " (" + std::to_string(fileCount) + ")");
            } else {
                newOutFile.replace(newOutFile.find_last_of('(') + 1, newOutFile.find_last_of(')'), std::to_string(fileCount));
                newOutFile += ").bmp";
            }
			outptr = fopen(newOutFile.c_str(), "r");

			if (outptr == NULL) {
				fclose(outptr);
				break;
			}

			fclose(outptr);
			fileCount++;
		}
	}

	// Open output file in write mode
	outptr = fopen(newOutFile.c_str(), "w");
    // DEBUG - PRINT newOutFile.c_str() and newOutFile
    printf("Output File: %s\n", newOutFile.c_str());
    std::cout << "Output File: " << newOutFile << std::endl;

	if (outptr == NULL) {
		fclose(inptr);
		return -2;
	}

	// Read infile's BITMAPFILEHEADER
	BITMAPFILEHEADER bf;
	fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

	// Read infile's BITMAPINFOHEADER
	BITMAPINFOHEADER bi;
	fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

	// Ensure infile is (likely) a 24-bit uncompressed BMP 4.0
	if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
		bi.biBitCount != 24 || bi.biCompression != 0) {
		fclose(outptr);
		fclose(inptr);
		printf("Unsupported file format.\n");
		return 1;
	}

	// Get image's dimensions
	int height = abs(bi.biHeight);
	int width = bi.biWidth;

	// Allocate memory for image
	std::vector<std::vector<RGBTRIPLE>> image(height, std::vector<RGBTRIPLE>(width));

	// Determine padding for scanlines
	int padding = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;

	// Iterate over infile's scanlines
	for (int i = 0; i < height; i++) {
		// Read row into pixel array
		fread(image[i].data(), sizeof(RGBTRIPLE), width, inptr);

		// Skip over padding
		fseek(inptr, padding, SEEK_CUR);
	}

	// Filter image
	// convert filter type to cpp string
    std::string filterTypeStr(filterType);
    std::cout << "Filter Type: " << filterTypeStr << std::endl;
    if (filterTypeStr == "Grayscale") {
        Grayscale(height, width, image);
    } else if (filterTypeStr == "Reflect") {
        Reflect(height, width, image);
    } else if (filterTypeStr == "Blur") {
        Blur(height, width, image);
    } else if (filterTypeStr == "Edge") {
        Edge(height, width, image);
    } else {
        fclose(outptr);
        fclose(inptr);
        return -3;
    }

	// Write outfile's BITMAPFILEHEADER
	fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

	// Write outfile's BITMAPINFOHEADER
	fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

	// Write new pixels to outfile
	for (int i = 0; i < height; i++) {
		// Write row to outfile
		fwrite(image[i].data(), sizeof(RGBTRIPLE), width, outptr);

		// Write padding at end of row
		for (int k = 0; k < padding; k++) {
			fputc(0x00, outptr);
		}
	}

	// // Free memory for image
	// free(image);
	// Not needed bc made the switch from pointer arrays to vectors

	// Close files
	fclose(inptr);
	fclose(outptr);
	return 0;
}