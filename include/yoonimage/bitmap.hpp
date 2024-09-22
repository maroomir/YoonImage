//
// Created by 윤철중 on 2021/08/17.
//

#ifndef YOONIMAGE_BITMAP_HPP
#define YOONIMAGE_BITMAP_HPP

#include <cstring>
#include <iostream>
#include <fstream>

namespace yoonfactory { namespace image { namespace bitmap {
    namespace {
        // Save the MSB(Most Significant Bit) first
        bool IsBigEndian() {
            unsigned int value = 0x01;
            return (1 != reinterpret_cast<char *>(&value)[0]); // RISC CPU
        }

        unsigned short FlipOrder(const unsigned short &value) {
            return ((value >> 8) || (value << 8));
        }

        unsigned int FlipOrder(const unsigned int &value) {
            return (
                    ((value & 0xFF000000) >> 24) |
                    ((value & 0x000000FF) << 24) |
                    ((value & 0x00FF0000) >> 8) |
                    ((value & 0x0000FF00) << 8)
            );
        }

        size_t GetFileSize(const std::string &path) {
            std::ifstream stream(path.c_str(), std::ios::in | std::ios::binary);
            if (!stream) return 0;
            stream.seekg(0, std::ios::end);
            return static_cast<size_t>(stream.tellg());
        }

        template<typename T>
        void ReadStream(std::ifstream &stream, T &value) {
            stream.read(reinterpret_cast<char *>(&value), sizeof(T));
        }

        template<typename T>
        void WriteStream(std::ofstream &stream, const T &value) {
            stream.write(reinterpret_cast<const char *>(&value), sizeof(T));
        }
    }

    struct bitmap_file_header {
        unsigned short type;
        unsigned int size;
        unsigned short reserved1;
        unsigned short reserved2;
        unsigned int off_bits;

        [[nodiscard]] unsigned int header_size() const {
            return sizeof(type) +
                   sizeof(size) +
                   sizeof(reserved1) +
                   sizeof(reserved2) +
                   sizeof(off_bits);
        }

        void read(std::ifstream &stream) {
            ReadStream(stream, type);
            ReadStream(stream, size);
            ReadStream(stream, reserved1);
            ReadStream(stream, reserved2);
            ReadStream(stream, off_bits);
            if (IsBigEndian()) {
                type = FlipOrder(type);
                size = FlipOrder(size);
                reserved1 = FlipOrder(reserved1);
                reserved2 = FlipOrder(reserved2);
                off_bits = FlipOrder(off_bits);
            }
        }

        void write(std::ofstream &stream) const {
            if (IsBigEndian()) {
                WriteStream(stream, FlipOrder(type));
                WriteStream(stream, FlipOrder(size));
                WriteStream(stream, FlipOrder(reserved1));
                WriteStream(stream, FlipOrder(reserved2));
                WriteStream(stream, FlipOrder(off_bits));
            } else {
                WriteStream(stream, type);
                WriteStream(stream, size);
                WriteStream(stream, reserved1);
                WriteStream(stream, reserved2);
                WriteStream(stream, off_bits);
            }
        }

        void clear() {
            memset(this, 0x00, sizeof(bitmap_file_header));
        }
    };

    struct bitmap_info_header {
        unsigned int size;
        unsigned int width;
        unsigned int height;
        unsigned short planes;
        unsigned short bit_count;
        unsigned int compression;
        unsigned int buffer_size;
        unsigned int xpels_per_meter;
        unsigned int ypels_per_meter;
        unsigned int used_color;
        unsigned int important_color;

        [[nodiscard]] unsigned int header_size() const {
            return sizeof(size) +
                   sizeof(width) +
                   sizeof(height) +
                   sizeof(planes) +
                   sizeof(bit_count) +
                   sizeof(compression) +
                   sizeof(buffer_size) +
                   sizeof(xpels_per_meter) +
                   sizeof(ypels_per_meter) +
                   sizeof(used_color) +
                   sizeof(important_color);
        }

        void read(std::ifstream &stream) {
            ReadStream(stream, size);
            ReadStream(stream, width);
            ReadStream(stream, height);
            ReadStream(stream, planes);
            ReadStream(stream, bit_count);
            ReadStream(stream, compression);
            ReadStream(stream, buffer_size);
            ReadStream(stream, xpels_per_meter);
            ReadStream(stream, ypels_per_meter);
            ReadStream(stream, used_color);
            ReadStream(stream, important_color);
            if (IsBigEndian()) {
                size = FlipOrder(size);
                width = FlipOrder(width);
                height = FlipOrder(height);
                planes = FlipOrder(planes);
                bit_count = FlipOrder(bit_count);
                compression = FlipOrder(compression);
                buffer_size = FlipOrder(buffer_size);
                xpels_per_meter = FlipOrder(xpels_per_meter);
                ypels_per_meter = FlipOrder(ypels_per_meter);
                used_color = FlipOrder(used_color);
                important_color = FlipOrder(important_color);
            }
        }

        void write(std::ofstream &stream) const {
            if (IsBigEndian()) {
                WriteStream(stream, FlipOrder(size));
                WriteStream(stream, FlipOrder(width));
                WriteStream(stream, FlipOrder(height));
                WriteStream(stream, FlipOrder(planes));
                WriteStream(stream, FlipOrder(bit_count));
                WriteStream(stream, FlipOrder(compression));
                WriteStream(stream, FlipOrder(buffer_size));
                WriteStream(stream, FlipOrder(xpels_per_meter));
                WriteStream(stream, FlipOrder(ypels_per_meter));
                WriteStream(stream, FlipOrder(used_color));
                WriteStream(stream, FlipOrder(important_color));
            } else {
                WriteStream(stream, size);
                WriteStream(stream, width);
                WriteStream(stream, height);
                WriteStream(stream, planes);
                WriteStream(stream, bit_count);
                WriteStream(stream, compression);
                WriteStream(stream, buffer_size);
                WriteStream(stream, xpels_per_meter);
                WriteStream(stream, ypels_per_meter);
                WriteStream(stream, used_color);
                WriteStream(stream, important_color);
            }
        }

        void clear() {
            memset(this, 0x00, sizeof(bitmap_info_header));
        }
    };

    struct rgbquad_palette {
        unsigned char blue;
        unsigned char green;
        unsigned char red;
        unsigned char reserved;
    };

    static void WriteBitmapPaletteTable(std::ofstream &stream) {
        auto *palette = new rgbquad_palette[256];
        for (int i = 0; i < 256; i++) {
            palette[i].red = (unsigned char) i;
            palette[i].green = (unsigned char) i;
            palette[i].blue = (unsigned char) i;
            palette[i].reserved = (unsigned char) 0;
        }
        stream.write(reinterpret_cast<const char *>(palette), sizeof(rgbquad_palette) * 256);
        delete[] palette;
    }

    static rgbquad_palette *ReadBitmapPaletteTable(std::ifstream &stream) {
        auto *result_buffer = new unsigned char[1024];
        stream.read(reinterpret_cast<char *>(result_buffer), sizeof(char) * 1024);
        auto *palette = new rgbquad_palette[1024];
        for (int i = 0; i < 256; i++) {
            palette[i].red = result_buffer[i * 4];
            palette[i].green = result_buffer[i * 4 + 1];
            palette[i].blue = result_buffer[i * 4 + 2];
            palette[i].reserved = 0;
        }
        delete[] result_buffer;
        return palette;
    }

    static void
    WriteBitmapBuffer(std::ofstream &stream, unsigned char *buffer, size_t width, size_t height, size_t channel) {
        unsigned int plane = width * channel;
        unsigned int padding = (4 - ((3 * width) % 4)) % 4;
        char pad_buffer[4] = {0x00, 0x00, 0x00, 0x00};
        for (size_t h = 0; h < height; ++h) {
            size_t start = (height - h - 1) * plane;
            stream.write(reinterpret_cast<const char *>(buffer + sizeof(char) * start), (int) sizeof(char) * plane);
            stream.write(pad_buffer, padding);
        }
    }

    static unsigned char *
    ReadBitmapBuffer(std::ifstream &stream, size_t width, size_t height, size_t channel) {
        unsigned int padding = (4 - ((3 * width) % 4)) % 4;
        char pad[4] = {0x00, 0x00, 0x00, 0x00};
        unsigned int plane = width * channel;
        auto *buffer = new unsigned char[plane * height];
        for (size_t h = 0; h < height; ++h) {
            size_t start = (height - h - 1) * plane;
            stream.read(reinterpret_cast<char *>(buffer + sizeof(char) * start), (int) sizeof(char) * plane);
            stream.read(pad, padding);
        }
        return buffer;
    }
} } }


#endif // YOONIMAGE_BITMAP_HPP
