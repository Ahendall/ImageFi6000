// C++ ADAPTATION OF CS50'S BMP HEADER FILE

#include <cstdint>  // C++ standard header for fixed-width integers

/**
 * Common Data Types
 */
typedef uint8_t  BYTE;
typedef uint32_t DWORD;
typedef int32_t  LONG;
typedef uint16_t WORD;

/**
 * BITMAPFILEHEADER
 * 
 * The BITMAPFILEHEADER structure contains information about the type, size,
 * and layout of a file that contains a DIB [device-independent bitmap].
 */
#pragma pack(push, 1)
struct BITMAPFILEHEADER
{
    WORD   bfType;
    DWORD  bfSize;
    WORD   bfReserved1;
    WORD   bfReserved2;
    DWORD  bfOffBits;
};
#pragma pack(pop)

/**
 * BITMAPINFOHEADER
 * 
 * The BITMAPINFOHEADER structure contains information about the
 * dimensions and color format of a DIB [device-independent bitmap].
 */
#pragma pack(push, 1)
struct BITMAPINFOHEADER
{
    DWORD  biSize;
    LONG   biWidth;
    LONG   biHeight;
    WORD   biPlanes;
    WORD   biBitCount;
    DWORD  biCompression;
    DWORD  biSizeImage;
    LONG   biXPelsPerMeter;
    LONG   biYPelsPerMeter;
    DWORD  biClrUsed;
    DWORD  biClrImportant;
};
#pragma pack(pop)

/**
 * RGBTRIPLE
 * 
 * This structure describes a color consisting of relative intensities of
 * red, green, and blue.
 */
#pragma pack(push, 1)
struct RGBTRIPLE
{
    BYTE  rgbtBlue;
    BYTE  rgbtGreen;
    BYTE  rgbtRed;
};
#pragma pack(pop)
