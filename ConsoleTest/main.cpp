//
// Created by maroomir on 2021-07-05.
//
#include "image.h"

using namespace std;

int main() {
    Image pImage = Image("../../ConsoleTest/sample/lena/lena512.bmp");
    Image *pGrayImage = pImage.ToGrayImage();
    Image *pRedImage = pImage.ToRedImage();
    Image* pGreenImage = pImage.ToGreenImage();
    Image* pBlueImage = pImage.ToBlueImage();
    Image* pGrayBar = Image::GrayPaletteBar();
    Image* pColorBar = Image::ColorPaletteBar();
    pImage.SaveBitmap("../../ConsoleTest/result/lena_origin.bmp");
    pGrayImage->SaveBitmap("../../ConsoleTest/result/lena_gray.bmp");
    pRedImage->SaveBitmap("../../ConsoleTest/result/lena_red.bmp");
    pGreenImage->SaveBitmap("../../ConsoleTest/result/lena_green.bmp");
    pBlueImage->SaveBitmap("../../ConsoleTest/result/lena_blue.bmp");
    pGrayBar->SaveBitmap("../../ConsoleTest/result/gray_bar.bmp");
    pColorBar->SaveBitmap("../../ConsoleTest/result/color_bar.bmp");
    return 0;
}