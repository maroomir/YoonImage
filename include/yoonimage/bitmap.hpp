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
        bool is_big_endian() {
            unsigned int value = 0x01;
            return (1 != reinterpret_cast<char *>(&value)[0]); // RISC CPU
        }

        unsigned short flip_order(const unsigned short &value) {
            return ((value >> 8) || (value << 8));
        }

        unsigned int flip_order(const unsigned int &value) {
            return (
                    ((value & 0xFF000000) >> 0x18) |
                    ((value & 0x000000FF) << 0x18) |
                    ((value & 0x00FF0000) >> 0x08) |
                    ((value & 0x0000FF00) << 0x08)
            );
        }

        size_t get_file_size(const std::string &path) {
            std::ifstream stream(path.c_str(), std::ios::in | std::ios::binary);
            if (!stream) return 0;
            stream.seekg(0, std::ios::end);
            return static_cast<size_t>(stream.tellg());
        }

        template<typename T>
        void read_stream(std::ifstream &stream, T &value) {
            stream.read(reinterpret_cast<char *>(&value), sizeof(T));
        }

        template<typename T>
        void write_stream(std::ofstream &stream, const T &value) {
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
            read_stream(stream, type);
            read_stream(stream, size);
            read_stream(stream, reserved1);
            read_stream(stream, reserved2);
            read_stream(stream, off_bits);
            if (is_big_endian()) {
                type = flip_order(type);
                size = flip_order(size);
                reserved1 = flip_order(reserved1);
                reserved2 = flip_order(reserved2);
                off_bits = flip_order(off_bits);
            }
        }

        void write(std::ofstream &stream) const {
            if (is_big_endian()) {
                write_stream(stream, flip_order(type));
                write_stream(stream, flip_order(size));
                write_stream(stream, flip_order(reserved1));
                write_stream(stream, flip_order(reserved2));
                write_stream(stream, flip_order(off_bits));
            } else {
                write_stream(stream, type);
                write_stream(stream, size);
                write_stream(stream, reserved1);
                write_stream(stream, reserved2);
                write_stream(stream, off_bits);
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
            read_stream(stream, size);
            read_stream(stream, width);
            read_stream(stream, height);
            read_stream(stream, planes);
            read_stream(stream, bit_count);
            read_stream(stream, compression);
            read_stream(stream, buffer_size);
            read_stream(stream, xpels_per_meter);
            read_stream(stream, ypels_per_meter);
            read_stream(stream, used_color);
            read_stream(stream, important_color);
            if (is_big_endian()) {
                size = flip_order(size);
                width = flip_order(width);
                height = flip_order(height);
                planes = flip_order(planes);
                bit_count = flip_order(bit_count);
                compression = flip_order(compression);
                buffer_size = flip_order(buffer_size);
                xpels_per_meter = flip_order(xpels_per_meter);
                ypels_per_meter = flip_order(ypels_per_meter);
                used_color = flip_order(used_color);
                important_color = flip_order(important_color);
            }
        }

        void write(std::ofstream &stream) const {
            if (is_big_endian()) {
                write_stream(stream, flip_order(size));
                write_stream(stream, flip_order(width));
                write_stream(stream, flip_order(height));
                write_stream(stream, flip_order(planes));
                write_stream(stream, flip_order(bit_count));
                write_stream(stream, flip_order(compression));
                write_stream(stream, flip_order(buffer_size));
                write_stream(stream, flip_order(xpels_per_meter));
                write_stream(stream, flip_order(ypels_per_meter));
                write_stream(stream, flip_order(used_color));
                write_stream(stream, flip_order(important_color));
            } else {
                write_stream(stream, size);
                write_stream(stream, width);
                write_stream(stream, height);
                write_stream(stream, planes);
                write_stream(stream, bit_count);
                write_stream(stream, compression);
                write_stream(stream, buffer_size);
                write_stream(stream, xpels_per_meter);
                write_stream(stream, ypels_per_meter);
                write_stream(stream, used_color);
                write_stream(stream, important_color);
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
