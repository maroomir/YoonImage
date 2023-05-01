//
// Created by maroomir on 2021-07-05.
//

#ifndef YOONIMAGE_IMAGE_H_
#define YOONIMAGE_IMAGE_H_

#include "figure.hpp"
#include "bitmap.hpp"
#include <string>

namespace yoonfactory {
    namespace image {
        constexpr int invalid_num = -65536;
        constexpr int default_channel = 1;
        constexpr int default_width = 640;
        constexpr int default_height = 480;

        typedef enum {
            FORMAT_NONE = -1,
            FORMAT_GRAY,
            FORMAT_RGB,
            FORMAT_RGB_PARALLEL,
            FORMAT_RGB_MIXED,
            FORMAT_BGR,
            FORMAT_BGR_PARALLEL,
            FORMAT_BGR_MIXED,
        } IMAGE_FORMAT;
    }

    class Image {
    private:
        static int ToChannel(image::IMAGE_FORMAT format);

        static image::IMAGE_FORMAT ToImageFormat(size_t channel);

        static unsigned char *ToByte(const int &number);

        static int ToInteger(const unsigned char *bytes);

        unsigned char *ToMixedColorBuffer(const unsigned char *buffer, bool reverse_order) const;

        unsigned char *ToParallelColorBuffer(const unsigned char *buffer, bool rgb_order) const;

    private:
        unsigned char *_buffer;  // "Gray" or Parallel Color Buffers (R + G + B)
        size_t _width, _height, _channel;
        image::IMAGE_FORMAT _format;

    public:
        Image();

        ~Image();

        Image(const Image &image);

        explicit Image(const std::string &image_path);

        Image(size_t width, size_t height, size_t channel);

        Image(int *buffer, size_t width, size_t height);

        Image(unsigned char *red_buffer, unsigned char *green_buffer, unsigned char *blue_buffer, size_t width,
              size_t height);

        Image(unsigned char *buffer, size_t width, size_t height, image::IMAGE_FORMAT format);

        [[nodiscard]] size_t Width() const;

        [[nodiscard]] size_t Height() const;

        [[nodiscard]] size_t Channel() const;

        [[nodiscard]] size_t Stride() const;

        unsigned char *GetBuffer();

        unsigned char *CopyBuffer();

        unsigned char *GetMixedColorBuffer();

        image::IMAGE_FORMAT ImageFormat();

        Image *ToGrayImage();

        Image *ToRedImage();

        Image *ToGreenImage();

        Image *ToBlueImage();

        unsigned char *ToGrayBuffer();

        unsigned char *ToRedBuffer();

        unsigned char *ToGreenBuffer();

        unsigned char *ToBlueBuffer();

        void CopyFrom(const Image &image);

        Image *Clone();

        bool Equals(const Image &image);

        bool LoadBitmap(const std::string &path);

        bool SaveBitmap(const std::string &path);

    public:
        static Image *GrayPaletteBar(int width = 256, int height = 50, int step=10);

        static Image *ColorPaletteBar(int width = 256, int height = 50, int step=10);
    };
}

#endif // YOONIMAGE_IMAGE_H_
