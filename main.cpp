//
// Created by maroomir on 2021-07-05.
//
// https://github.com/ArashPartow/bitmap#readme
#include "bitmap_image.hpp"
#include "src/Image.h"
#include "src/enum.h"

using namespace std;
using namespace YoonImage;

void save_image(Image* pImage, const string strPath) {
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

Image* load_image(string strPath) {
    bitmap_image pSourceBitmap(strPath);
    int nWidth = pSourceBitmap.width();
    int nHeight = pSourceBitmap.height();
    auto *pSourceImage = new Image(pSourceBitmap.data(), nWidth, nHeight, FORMAT_BGR_MIXED);
    return pSourceImage;
}

int main() {
    Image *pImage = load_image("../sample/lena/lena512.bmp");
    Image *pGrayImage = pImage->ToGrayImage();
    save_image(pImage, "../result/lena_origin.bmp");
    save_image(pGrayImage, "../result/lena_gray.bmp");
    return 0;
}