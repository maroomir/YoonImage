//
// Created by maroomir on 2021-07-05.
//

#ifndef YOONIMAGE_IMAGE_HPP
#define YOONIMAGE_IMAGE_HPP

#include "figure.hpp"
#include "bitmap.hpp"
#include "jpeg.hpp"
#include <string>

namespace yoonfactory {
    namespace image {
        constexpr int invalid_num = -65536;
        constexpr int default_channel = 1;
        constexpr int default_width = 640;
        constexpr int default_height = 480;
        constexpr int max_channel = 3;

        typedef enum {
            FORMAT_NONE = -1,
            FORMAT_GRAY,
            FORMAT_RGB,
            FORMAT_RGB_PARALLEL,
            FORMAT_RGB_MIXED,
            FORMAT_BGR,
            FORMAT_BGR_PARALLEL,
            FORMAT_BGR_MIXED,
            MAX_IMAGE_FORMAT
        } IMAGE_FORMAT;

        typedef enum {
            FILE_NONE = -1,
            FILE_BITMAP = 0,
            FILE_JPEG,
            MAX_FILE_FORMAT
        } FILE_FORMAT;

        constexpr int format_to_channel[MAX_IMAGE_FORMAT] = {
                1, 3, 3, 3, 3, 3, 3
        };
        constexpr IMAGE_FORMAT channel_to_default_format[max_channel] = {
                FORMAT_GRAY, FORMAT_NONE, FORMAT_RGB
        };
    }

    static unsigned char *ToByte(const int &number) {
        auto* bytes = new unsigned char[4];
        bytes[0] = (number & 0xFF);
        bytes[1] = (number >> 8) & 0xFF;
        bytes[2] = (number >> 16) & 0xFF;
        bytes[3] = (number >> 24) & 0xFF;
        return bytes;
    }

    static int ToInteger(const unsigned char *bytes) {
        if (bytes == nullptr) return image::invalid_num;
        return bytes[0] | bytes[1] << 8 | bytes[2] << 16 | bytes[3] << 24;
    }

    class Image {
    private:
        unsigned char *_to_mixed_color_buffer(const unsigned char *buffer, bool reverse_order = false) const;

        unsigned char *_to_parallel_color_buffer(const unsigned char *buffer, bool reverse_order = false) const;

    private:
        unsigned char *_buffer;  // "Gray" or Parallel Color Buffers (R + G + B)
        size_t _width, _height, _channel;
        image::IMAGE_FORMAT _format;

    public:
        Image();

        ~Image();

        Image(const Image &image);

        explicit Image(const std::string &image_path, image::FILE_FORMAT format);

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

        bool LoadJpeg(const std::string &path);

        bool SaveJpeg(const std::string &path);

    public:
        static Image *GrayPaletteBar(int width = 256, int height = 50, int step = 10);

        static Image *ColorPaletteBar(int width = 256, int height = 50, int step = 10);
    };
}

#endif // YOONIMAGE_IMAGE_HPP
