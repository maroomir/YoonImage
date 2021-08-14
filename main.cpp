//
// Created by maroomir on 2021-07-05.
//
#include <iostream>
#include "bitmap_image.hpp"  // https://github.com/ArashPartow/bitmap#readme
#include "src/Image.h"
#include "src/enum.h"

void save_image(YoonImage* pImage, const string strPath) {
    int nWidth = pImage->GetWidth();
    int nHeight = pImage->GetHeight();
    bitmap_image pResultBitmap(nWidth, nHeight);
    switch(pImage->GetChannel())
    {
        case 1:
        {
            unsigned char* pBuffer = pImage->GetBuffer();
            for (int x = 0; x < nWidth; x++) {
                for (int y = 0; y < nHeight; y++) {
                    unsigned char nLevel = pBuffer[y * nWidth + x];
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
            for (int x = 0; x < nWidth; x++) {
                for (int y = 0; y < nHeight; y++) {
                    unsigned char nRed = pRedBuffer[y * nWidth + x];
                    unsigned char nGreen = pGreenBuffer[y * nWidth + x];
                    unsigned char nBlue = pBlueBuffer[y * nWidth + x];
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
    bitmap_image pSourceBitmap(strPath);
    int nWidth = pSourceBitmap.width();
    int nHeight = pSourceBitmap.height();
    int nChannel = 3;
    auto *pBuffer = new unsigned char[sizeof(char) * nWidth * nHeight * nChannel];
    for (int x = 0; x < nWidth; x++) {
        for (int y = 0; y < nHeight; y++) {
            unsigned char nRed;
            unsigned char nGreen;
            unsigned char nBlue;
            pSourceBitmap.get_pixel(x, y, nRed, nGreen, nBlue);
            pBuffer[y * nWidth * nChannel + x * nChannel] = nRed;
            pBuffer[y * nWidth * nChannel + x * nChannel + 1] = nGreen;
            pBuffer[y * nWidth * nChannel + x * nChannel + 2] = nBlue;
        }
    }
    auto *pSourceImage = new YoonImage(pBuffer, nWidth, nHeight, FORMAT_RGB_MIXED);
    delete[] pBuffer;
    return pSourceImage;
}

int main(){
    YoonImage* pImage = load_image("../sample/lena/lena512.bmp");
    YoonImage* pGrayImage = pImage->ToGrayImage();
    save_image(pImage, "../result/lena_origin.bmp");
    save_image(pGrayImage, "../result/lena_gray.bmp");
    return 0;
}