//
// Created by maroomir on 2021-07-05.
//
#include <iostream>
#include "bitmap_image.hpp"  // https://github.com/ArashPartow/bitmap#readme
#include "src/Image.h"
#include "src/enum.h"

void save_bitmap(YoonImage* pImage, const string strPath) {
    bitmap_image pResultBitmap(pImage->GetWidth(), pImage->GetHeight());
    unsigned char *pBuffer = pImage->GetBuffer();
    for (int x = 0; x < pImage->GetWidth(); x++) {
        for (int y = 0; y < pImage->GetHeight(); y++) {
            unsigned char nLevel = pBuffer[y * pImage->GetWidth() + x];
            pResultBitmap.set_pixel(x, y, nLevel, nLevel, nLevel);
        }
    }
    pResultBitmap.save_image(strPath);
}

int main(){
    bitmap_image pSourceBitmap ("./sample/align/mark.bmp");
    YoonImage* pImage = new YoonImage(pSourceBitmap.data(), pSourceBitmap.width(), pSourceBitmap.height(), FORMAT_RGB);
    YoonImage* pGrayImage = pImage->ToGrayImage();
    save_bitmap(pGrayImage, "./result/convert.bmp");

    delete pImage;
    delete pGrayImage;
    return 0;
}