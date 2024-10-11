#include "bmp.h"

// Convert image to grayscale
void Grayscale(int height, int width, RGBTRIPLE (*image)[width]);

// Reflect image horizontally
void Reflect(int height, int width, RGBTRIPLE (*image)[width]);

// Detect edges
void Edge(int height, int width, RGBTRIPLE (*image)[width]);

// Blur image
void Blur(int height, int width, RGBTRIPLE (*image)[width]);

// Convert to Sepia
void Sepia(int height, int width, RGBTRIPLE (*image)[width]);
