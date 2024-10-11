#include "helpers.h"
#include <utility>
#include <cmath>

// Convert image to grayscale
void Grayscale(int height, int width, vector<vector<RGBTRIPLE>> &image) {
	// Formula: Average of RGB values
	// Time complexity: O(N) where N = width * height
	// Space complexity: O(1)
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			float avg = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3;
			image[i][j].rgbtRed = (BYTE)avg;
			image[i][j].rgbtGreen = (BYTE)avg;
			image[i][j].rgbtBlue = (BYTE)avg;
		}
	}

	return;
}

// Reflect image horizontally
void Reflect(int height, int width, vector<vector<RGBTRIPLE>> &image) {
	// Time complexity: O(N) where N = width * height
	// Space complexity: O(1)

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width / 2; j++) {
			RGBTRIPLE temp = move(image[i][j]);
			image[i][j] = move(image[i][width - 1 - j]);
			image[i][width - 1 - j] = move(temp);
		}
	}

	return;
}

// Blur image
void Blur(int height, int width, vector<vector<RGBTRIPLE>> &image) {
	// Formula: 3x3 box blur
	// Time complexity: O(N); N = width * height
	// Space complexity: O(N); N = width * height
	vector<vector<RGBTRIPLE>> temp = image;

	// Iterate through whole image
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			double redSum = 0, greenSum = 0, blueSum = 0;
			int count = 0;

			// Iterate through neighboring pixels
			for (int neighbor_Y = i - 1; neighbor_Y <= i + 1; neighbor_Y++) {
				for (int neighbor_X = j - 1; neighbor_X <= j + 1; neighbor_X++) {
					// verify that target pixel is within image bounds
					if (neighbor_X >= 0 &&
						neighbor_X < width &&
						neighbor_Y >= 0 &&
						neighbor_Y < height) {
                            count++;
                            redSum += temp[neighbor_Y][neighbor_X].rgbtRed;
                            greenSum += temp[neighbor_Y][neighbor_X].rgbtGreen;
                            blueSum += temp[neighbor_Y][neighbor_X].rgbtBlue;
					}
				}
			}

            // Apply Updated Values
            image[i][j].rgbtRed = (BYTE) (redSum / count);
            image[i][j].rgbtGreen = (BYTE) (greenSum / count);
            image[i][j].rgbtBlue = (BYTE) (blueSum / count);
		}
	}

	return;
}

// Detect edges
void Edge(int height, int width, vector<vector<RGBTRIPLE>> &image) {
    // Formula: Multi-Chanel Sobel Operator
    // Time Complexity: 
    // Space Complexity: 
    vector<vector<RGBTRIPLE>> temp = image;

    // Define the Sobel kernels
    const int Gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    const int Gy[3][3] = {
        { 1,  2,  1},
        { 0,  0,  0},
        {-1, -2, -1}
    };

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // Define weighted sums for each pixel
            int GxR = 0, GyR = 0;
            int GxG = 0, GyG = 0;
            int GxB = 0, GyB = 0;

            // Iterate through neighbors
            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    // Verify target pixel within bounds
                    if (i + k >= 0 &&
						i + k < height &&
						j + l >= 0 &&
						j + l < width) {
                            // Apply operator to each channel
                            GxR += temp[i + k][j + l].rgbtRed * Gx[k + 1][l + 1];
                            GyR += temp[i + k][j + l].rgbtRed * Gy[k + 1][l + 1];

                            GxG += temp[i + k][j + l].rgbtGreen * Gx[k + 1][l + 1];
                            GyG += temp[i + k][j + l].rgbtGreen * Gy[k + 1][l + 1];

                            GxB += temp[i + k][j + l].rgbtBlue * Gx[k + 1][l + 1];
                            GyB += temp[i + k][j + l].rgbtBlue * Gy[k + 1][l + 1];
					}
                }
            }

            // Apply Combination formula (why is it pythagoras bruh)
            int combRed = round(sqrt((GxR * GxR) + (GyR * GyR)));
            int combGreen = round(sqrt((GxG * GxG) + (GyG * GyG)));
            int combBlue = round(sqrt((GxB * GxB) + (GyB * GyB)));

            image[i][j].rgbtRed = (BYTE) min(combRed, 255);
            image[i][j].rgbtGreen = (BYTE) min(combGreen, 255);
            image[i][j].rgbtBlue = (BYTE) min(combBlue, 255);
        }
    }
    
    return;
}

// Convert to Sepia
void Sepia(int height, int width, vector<vector<RGBTRIPLE>> &image) {
    /*
        Formula:
        sepiaRed = .393(red) + .769(green) + .189(blue)
        sepiaGreen = .349(red) + .686(green) + .168(blue)
        sepiaBlue = .272(red) + .534(green) + .131(blue)
    */
    // Time complexity: O(N) where N = width * height
    // Space complexity: O(1)

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int sepiaRed = (int)(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = (int)(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = (int)(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            // Cap the values at 255
            image[i][j].rgbtRed = (BYTE)min(sepiaRed, 255);
            image[i][j].rgbtGreen = (BYTE)min(sepiaGreen, 255);
            image[i][j].rgbtBlue = (BYTE)min(sepiaBlue, 255);
        }
    }

	return;
}