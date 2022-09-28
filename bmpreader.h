/**
 * Workaround for reading BMP in non-Windows.
 * Based on https://cboard.cprogramming.com/game-programming/76871-loading-bitmap-without-using-glaux.html.
 * 
 * Author: Muntashir Al-Islam <muntashirakon@riseup.net>
 */

#ifndef _H_BMP_READER
#define _H_BMP_READER

#include <stdlib.h>
#ifdef __APPLE__
#include <OpenGL/gltypes.h>
#else // Other non-windows platform
#include <GL/gltypes.h>
#endif

#define BITMAP_ID 0x4D42

#pragma pack(push)
#pragma pack(1)
typedef struct _Bitmap_File_Header
{
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
} Bitmap_File_Header;

typedef struct _Bitmap_Info_Header
{
    uint32_t biSize;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} Bitmap_Info_Header;
#pragma pack(pop)

/*
 * RGB Image Structure
 */
typedef struct _AUX_RGBImageRec
{
    GLint sizeX, sizeY;
    unsigned char *data;
} AUX_RGBImageRec;

AUX_RGBImageRec *auxDIBImageLoad(const char *filename);

#endif // _H_BMP_READER
