//
// Created by maroomir on 2021-07-05.
//
#include "src/Image.h"

using namespace std;

int main() {
    YoonImage pImage = YoonImage("../sample/lena/lena512.bmp");
    YoonImage *pGrayImage = pImage.ToGrayImage();
    YoonImage *pRedImage = pImage.ToRedImage();
    YoonImage* pGreenImage = pImage.ToGreenImage();
    YoonImage* pBlueImage = pImage.ToBlueImage();
    YoonImage* pGrayBar = YoonImage::GrayPaletteBar();
    YoonImage* pColorBar = YoonImage::ColorPaletteBar();
    pImage.SaveBitmap("../result/lena_origin.bmp");
    pGrayImage->SaveBitmap("../result/lena_gray.bmp");
    pRedImage->SaveBitmap("../result/lena_red.bmp");
    pGreenImage->SaveBitmap("../result/lena_green.bmp");
    pBlueImage->SaveBitmap("../result/lena_blue.bmp");
    pGrayBar->SaveBitmap("../result/gray_bar.bmp");
    pColorBar->SaveBitmap("../result/color_bar.bmp");
    return 0;
}