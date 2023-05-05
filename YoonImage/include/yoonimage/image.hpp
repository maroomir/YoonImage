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

        typedef enum {
            FILE_NONE = -1,
            FILE_BITMAP = 0,
            FILE_JPEG = 1,
        } FILE_FORMAT;

        static int ToChannel(IMAGE_FORMAT format) {
            int channel = invalid_num;
            switch (format) {
                case FORMAT_GRAY:
                    channel = 1;
                    break;
                case FORMAT_RGB:
                case FORMAT_RGB_PARALLEL:
                case FORMAT_RGB_MIXED:
                case FORMAT_BGR:
                case FORMAT_BGR_PARALLEL:
                case FORMAT_BGR_MIXED:
                    channel = 3;
                    break;
                default:
                    std::printf("[Image][ToChannel] Abnormal Image Format\n");
                    break;
            }
            return channel;
        }

        static IMAGE_FORMAT ToImageFormat(size_t channel) {
            IMAGE_FORMAT format = FORMAT_NONE;
            switch (channel) {
                case 1:
                    format = FORMAT_GRAY;
                    break;
                case 3:
                    format = FORMAT_RGB;
                    break;
                default:
                    std::printf("[Image][ToImageFormat] Abnormal Image Channel\n");
                    break;
            }
            return format;
        }
    }

    static unsigned char *ToByte(const int &number) {
        auto* bytes = new unsigned char[4];
        bytes[0] = (number & 0x000000ff);
        bytes[1] = (number & 0x0000ff00) >> 8;
        bytes[2] = (number & 0x00ff0000) >> 16;
        bytes[3] = (number & 0xff000000) >> 24;
        return bytes;
    }

    static int ToInteger(const unsigned char *bytes) {
        int num = image::invalid_num;
        if (bytes != nullptr) {
            num += (bytes[0] & 0x000000ff);
            num += (bytes[1] & 0x000000ff) << 8;
            num += (bytes[2] & 0x000000ff) << 16;
            num += (bytes[3] & 0x000000ff) << 24;
        }
        return num;
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
