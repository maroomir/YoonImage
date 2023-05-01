//
// Created by 윤철중 on 2021/08/17.
//

#ifndef YOONIMAGE_BITMAP_H_
#define YOONIMAGE_BITMAP_H_

#include <cstring>
#include <iostream>
#include <fstream>

namespace yoonfactory::bitmap {
    struct bitmap_file_header {
        unsigned short type;
        unsigned int size;
        unsigned short reserved1;
        unsigned short reserved2;
        unsigned int off_bits;

        [[nodiscard]] unsigned int headerSize() const {
            return sizeof(type) +
                   sizeof(size) +
                   sizeof(reserved1) +
                   sizeof(reserved2) +
                   sizeof(off_bits);
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

        [[nodiscard]] unsigned int headerSize() const {
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

    namespace {
        // Save the MSB(Most Significant Bit) first
        bool IsBigEndian() {
            unsigned int value = 0x01;
            return (1 != reinterpret_cast<char *>(&value)[0]); // RISC CPU
        }

        unsigned short flipOrder(const unsigned short &value) {
            return ((value >> 8) || (value << 8));
        }

        unsigned int flipOrder(const unsigned int &value) {
            return (
                    ((value & 0xFF000000) >> 0x18) |
                    ((value & 0x000000FF) << 0x18) |
                    ((value & 0x00FF0000) >> 0x08) |
                    ((value & 0x0000FF00) << 0x08)
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

    static void ReadBitmapFileHeader(std::ifstream &stream, bitmap_file_header &header) {
        ReadStream(stream, header.type);
        ReadStream(stream, header.size);
        ReadStream(stream, header.reserved1);
        ReadStream(stream, header.reserved2);
        ReadStream(stream, header.off_bits);
        if (IsBigEndian()) {
            header.type = flipOrder(header.type);
            header.size = flipOrder(header.size);
            header.reserved1 = flipOrder(header.reserved1);
            header.reserved2 = flipOrder(header.reserved2);
            header.off_bits = flipOrder(header.off_bits);
        }
    }

    static void ReadBitmapInfoHeader(std::ifstream &stream, bitmap_info_header &header) {
        ReadStream(stream, header.size);
        ReadStream(stream, header.width);
        ReadStream(stream, header.height);
        ReadStream(stream, header.planes);
        ReadStream(stream, header.bit_count);
        ReadStream(stream, header.compression);
        ReadStream(stream, header.buffer_size);
        ReadStream(stream, header.xpels_per_meter);
        ReadStream(stream, header.ypels_per_meter);
        ReadStream(stream, header.used_color);
        ReadStream(stream, header.important_color);
        if (IsBigEndian()) {
            header.size = flipOrder(header.size);
            header.width = flipOrder(header.width);
            header.height = flipOrder(header.height);
            header.planes = flipOrder(header.planes);
            header.bit_count = flipOrder(header.bit_count);
            header.compression = flipOrder(header.compression);
            header.buffer_size = flipOrder(header.buffer_size);
            header.xpels_per_meter = flipOrder(header.xpels_per_meter);
            header.ypels_per_meter = flipOrder(header.ypels_per_meter);
            header.used_color = flipOrder(header.used_color);
            header.important_color = flipOrder(header.important_color);
        }
    }

    static void WriteBitmapFileHeader(std::ofstream &stream, bitmap_file_header &header) {
        if (IsBigEndian()) {
            WriteStream(stream, flipOrder(header.type));
            WriteStream(stream, flipOrder(header.size));
            WriteStream(stream, flipOrder(header.reserved1));
            WriteStream(stream, flipOrder(header.reserved2));
            WriteStream(stream, flipOrder(header.off_bits));
        } else {
            WriteStream(stream, header.type);
            WriteStream(stream, header.size);
            WriteStream(stream, header.reserved1);
            WriteStream(stream, header.reserved2);
            WriteStream(stream, header.off_bits);
        }
    }

    static void WriteBitmapInfoHeader(std::ofstream &stream, bitmap_info_header &header) {
        if (IsBigEndian()) {
            WriteStream(stream, flipOrder(header.size));
            WriteStream(stream, flipOrder(header.width));
            WriteStream(stream, flipOrder(header.height));
            WriteStream(stream, flipOrder(header.planes));
            WriteStream(stream, flipOrder(header.bit_count));
            WriteStream(stream, flipOrder(header.compression));
            WriteStream(stream, flipOrder(header.buffer_size));
            WriteStream(stream, flipOrder(header.xpels_per_meter));
            WriteStream(stream, flipOrder(header.ypels_per_meter));
            WriteStream(stream, flipOrder(header.used_color));
            WriteStream(stream, flipOrder(header.important_color));
        } else {
            WriteStream(stream, header.size);
            WriteStream(stream, header.width);
            WriteStream(stream, header.height);
            WriteStream(stream, header.planes);
            WriteStream(stream, header.bit_count);
            WriteStream(stream, header.compression);
            WriteStream(stream, header.buffer_size);
            WriteStream(stream, header.xpels_per_meter);
            WriteStream(stream, header.ypels_per_meter);
            WriteStream(stream, header.used_color);
            WriteStream(stream, header.important_color);
        }
    }

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
            stream.write(reinterpret_cast<const char *>(buffer + sizeof(char) * start), (int)sizeof(char) * plane);
            stream.write(pad_buffer, padding);
        }
    }

    static unsigned char *
    ReadBitmapBuffer(std::ifstream &stream, const std::string &path, size_t width, size_t height, size_t channel) {
        unsigned int padding = (4 - ((3 * width) % 4)) % 4;
        char pad[4] = {0x00, 0x00, 0x00, 0x00};
        unsigned int plane = width * channel;
        auto *buffer = new unsigned char[plane * height];
        for (size_t h = 0; h < height; ++h) {
            size_t start = (height - h - 1) * plane;
            stream.read(reinterpret_cast<char *>(buffer + sizeof(char) * start), (int)sizeof(char) * plane);
            stream.read(pad, padding);
        }
        return buffer;
    }
}


#endif // YOONIMAGE_BITMAP_H_
