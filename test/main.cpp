//
// Created by maroomir on 2021-07-05.
//
#include <filesystem>
#include "yoonimage/image.hpp"

#ifdef PREDEFINE_PATH
#define TEST_PATH "../../../yoonimage"
#endif

void mkdir (const std::string& path) {
    std::filesystem::path path_ctl(path);
    if (std::filesystem::is_directory(path))
        return;
    std::filesystem::create_directories(path);
}

int main(int argc, char** argv) {
    using namespace yoonfactory;
#ifdef PREDEFINE_PATH
    std::string root_path = TEST_PATH;
#else
    std::string root_path = argv[0];
#endif
    if (root_path.back() != '/') {
        root_path += "/";
    }
    Image image = Image(root_path + "sample/lena/lena512.jpg", image::FILE_JPEG);
    Image *pGrayImage = image.ToGrayImage();
    Image *pRedImage = image.ToRedImage();
    Image* pGreenImage = image.ToGreenImage();
    Image* pBlueImage = image.ToBlueImage();
    Image* pGrayBar = Image::GrayPaletteBar();
    Image* pColorBar = Image::ColorPaletteBar();

    std::string result_path = root_path + "result/";
    mkdir(result_path);
    image.SaveBitmap(result_path + "lena_origin.bmp");
    pGrayImage->SaveBitmap(result_path + "lena_gray.bmp");
    pRedImage->SaveBitmap(result_path + "lena_red.bmp");
    pGreenImage->SaveBitmap(result_path + "lena_green.bmp");
    pBlueImage->SaveBitmap(result_path + "lena_blue.bmp");
    pGrayBar->SaveJpeg(result_path + "gray_bar.jpg");
    pColorBar->SaveJpeg(result_path + "color_bar.jpg");
    return 0;
}