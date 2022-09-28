/**
 * Workaround for reading BMP in non-Windows.
 * Based on https://cboard.cprogramming.com/game-programming/76871-loading-bitmap-without-using-glaux.html.
 * 
 * Author: Muntashir Al-Islam <muntashirakon@riseup.net>
 */

#ifndef _H_BMP_READER
#define _H_BMP_READER

#include <stdio.h>
#include <stdlib.h>
#include <OpenGL/gltypes.h>

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

AUX_RGBImageRec *auxDIBImageLoad(const char *filename)
{
    Bitmap_Info_Header bitmapInfoHeader;
    Bitmap_File_Header bitmapFileHeader;
    unsigned char *bitmapImage;
    AUX_RGBImageRec *img;
    int imageIdx = 0;
    unsigned char tempRGB;
    int len;
    FILE *f;

    if (!filename)
    {
        fprintf(stderr, "auxDIBImageLoad: Empty filename!\n");
        return NULL;
    }

    f = fopen(filename, "r");

    if (!f) {
        fprintf(stderr, "auxDIBImageLoad: Could not open %s!\n", filename);
        return NULL;
    }

    fread(&bitmapFileHeader, sizeof(Bitmap_File_Header), 1, f);
    if (bitmapFileHeader.bfType != BITMAP_ID)
    {
        fprintf(stderr, "auxDIBImageLoad: Invalid bitmap!\n");
        return NULL;
    }

    fread(&bitmapInfoHeader, sizeof(Bitmap_Info_Header), 1, f);

    len = bitmapInfoHeader.biSizeImage;
    bitmapImage = new unsigned char[len];

    fread(bitmapImage, len, 1, f);

    fclose(f);

    for (imageIdx = 0; imageIdx < len; imageIdx += 3)
    {
        tempRGB = bitmapImage[imageIdx];
        bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
        bitmapImage[imageIdx + 2] = tempRGB;
    }

    img = new AUX_RGBImageRec();
    img->sizeX = bitmapInfoHeader.biWidth;
    img->sizeY = bitmapInfoHeader.biHeight;
    img->data = bitmapImage;

    // printf("AUX_RGBImageRec(filename=%s, length=%d, width=%d, height=%d)\n", filename, len, img->sizeX, img->sizeY);
    return img;
}

#endif // _H_BMP_READER