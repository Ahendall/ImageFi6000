#include "helpers.h"

// Convert image to grayscale
void Grayscale(int height, int width, vector<vector<RGBTRIPLE>> &image) {
	// Formula: Average of RGB values
    // Time complexity: O(N) where N = m * n
    // Space complexity: O(1)
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            float avg = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3;
            image[i][j].rgbtRed = (BYTE) avg;
            image[i][j].rgbtGreen = (BYTE) avg;
            image[i][j].rgbtBlue = (BYTE) avg;
        }
    }
    
    return;
}

// Reflect image horizontally
void Reflect(int height, int width, vector<vector<RGBTRIPLE>> &image) {
	return;
}

// Blur image
void Blur(int height, int width, vector<vector<RGBTRIPLE>> &image) {
	return;
}

// Detect edges
void Edge(int height, int width, vector<vector<RGBTRIPLE>> &image) {
	return;
}

// Convert to Sepia
void Sepia(int height, int width, vector<vector<RGBTRIPLE>> &image) {
    return;
}