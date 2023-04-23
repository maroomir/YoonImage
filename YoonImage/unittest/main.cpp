//
// Created by maroomir on 2021-07-05.
//
#include "yoonimage/image.h"

using namespace std;

int main() {
    Image image = Image("../../../yoonimage/sample/lena/lena512.bmp");
    Image *pGrayImage = image.ToGrayImage();
    Image *pRedImage = image.ToRedImage();
    Image* pGreenImage = image.ToGreenImage();
    Image* pBlueImage = image.ToBlueImage();
    Image* pGrayBar = Image::GrayPaletteBar();
    Image* pColorBar = Image::ColorPaletteBar();
    image.SaveBitmap("../../../yoonimage/result/lena_origin.bmp");
    pGrayImage->SaveBitmap("../../../yoonimage/result/lena_gray.bmp");
    pRedImage->SaveBitmap("../../../yoonimage/result/lena_red.bmp");
    pGreenImage->SaveBitmap("../../../yoonimage/result/lena_green.bmp");
    pBlueImage->SaveBitmap("../../../yoonimage/result/lena_blue.bmp");
    pGrayBar->SaveBitmap("../../../yoonimage/result/gray_bar.bmp");
    pColorBar->SaveBitmap("../../../yoonimage/result/color_bar.bmp");
    return 0;
}