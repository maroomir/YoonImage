//
// Created by maroomir on 2021-07-05.
//
#include <iostream>
#include "bitmap_image.hpp"  // https://github.com/ArashPartow/bitmap#readme
#include "src/Image.h"
#include "src/enum.h"

void save_image(YoonImage* pImage, const string strPath) {
    bitmap_image pResultBitmap(pImage->GetWidth(), pImage->GetHeight());
    switch(pImage->GetChannel())
    {
        case 1:
        {
            unsigned char* pBuffer = pImage->GetBuffer();
            for (int x = 0; x < pImage->GetWidth(); x++) {
                for (int y = 0; y < pImage->GetHeight(); y++) {
                    unsigned char nLevel = pBuffer[y * pImage->GetWidth() + x];
                    pResultBitmap.set_pixel(x, y, nLevel, nLevel, nLevel);
                }
            }
            delete pBuffer;
            break;
        }
        case 3:
        {
            unsigned char* pRedBuffer = pImage->ToRedImage()->GetBuffer();
            unsigned char* pBlueBuffer = pImage->ToBlueImage()->GetBuffer();
            unsigned char* pGreenBuffer = pImage->ToGreenImage()->GetBuffer();
            for (int x = 0; x < pImage->GetWidth(); x++) {
                for (int y = 0; y < pImage->GetHeight(); y++) {
                    unsigned char nRed = pRedBuffer[y * pImage->GetWidth() + x];
                    unsigned char nGreen = pGreenBuffer[y * pImage->GetWidth() + x];
                    unsigned char nBlue = pBlueBuffer[y * pImage->GetWidth() + x];
                    pResultBitmap.set_pixel(x, y, nRed, nGreen, nBlue);
                }
            }
            delete pRedBuffer;
            delete pBlueBuffer;
            delete pGreenBuffer;
            break;
        }
        default:
            break;
    }
    pResultBitmap.save_image(strPath);
}

YoonImage* load_image(string strPath) {
    bitmap_image pSourceBitmap (strPath);
}

int main(){
    bitmap_image pSourceBitmap ("../sample/lena/lena512.bmp");
    YoonImage* pImage = new YoonImage(pSourceBitmap.data(), pSourceBitmap.width(), pSourceBitmap.height(), FORMAT_RGB);
    YoonImage* pGrayImage = pImage->ToGrayImage();
    save_image(pImage, "../result/lena_origin.bmp");
    save_image(pGrayImage, "../result/lena_gray.bmp");
    return 0;
}