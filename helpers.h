#include "bmp.h"
#include <vector>
using namespace std;

// Convert image to grayscale
void Grayscale(int height, int width, vector<vector<RGBTRIPLE>> &image);

// Reflect image horizontally
void Reflect(int height, int width, vector<vector<RGBTRIPLE>> &image);

// Detect edges
void Edge(int height, int width, vector<vector<RGBTRIPLE>> &image);

// Blur image
void Blur(int height, int width, vector<vector<RGBTRIPLE>> &image);

// Convert to Sepia
void Sepia(int height, int width, vector<vector<RGBTRIPLE>> &image);
