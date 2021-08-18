//
// Created by maroomir on 2021-07-05.
//
// https://github.com/ArashPartow/bitmap#readme
#include "bitmap_image.hpp"
#include "src/Image.h"
#include "src/enum.h"

using namespace std;

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
            unsigned char* pRedBuffer = pImage->ToRedBuffer();
            unsigned char* pBlueBuffer = pImage->ToBlueBuffer();
            unsigned char* pGreenBuffer = pImage->ToGreenBuffer();
            for (int x = 0; x < nWidth; x++) {
                for (int y = 0; y < nHeight; y++) {
                    unsigned char nRed = pRedBuffer[y * nWidth + x];
                    unsigned char nGreen = pGreenBuffer[y * nWidth + x];
                    unsigned char nBlue = pBlueBuffer[y * nWidth + x];
                    pResultBitmap.set_pixel(x, y, nRed, nGreen, nBlue);
                }
            }
            delete[] pRedBuffer;
            delete[] pBlueBuffer;
            delete[] pGreenBuffer;
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
    auto *pSourceImage = new YoonImage(pSourceBitmap.data(), nWidth, nHeight, FORMAT_BGR_MIXED);
    return pSourceImage;
}

int main() {
    YoonImage pImage = YoonImage("../sample/lena/lena512.bmp");
    YoonImage *pGrayImage = pImage.ToGrayImage();
    pImage.SaveBitmap("../result/lena_origin.bmp");
    pGrayImage->SaveBitmap("../result/lena_gray.bmp");
    return 0;
}