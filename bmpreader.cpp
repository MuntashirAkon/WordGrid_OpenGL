/**
 * Workaround for reading BMP in non-Windows.
 * Based on https://cboard.cprogramming.com/game-programming/76871-loading-bitmap-without-using-glaux.html.
 * 
 * Author: Muntashir Al-Islam <muntashirakon@riseup.net>
 */

#include <stdio.h>
#include "bmpreader.h"

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
