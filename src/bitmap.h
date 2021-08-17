//
// Created by 윤철중 on 2021/08/17.
//

#ifndef YOONIMAGE_BITMAP_H
#define YOONIMAGE_BITMAP_H

#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

struct BITMAP_FILE_HEADER {
    unsigned short type;
    unsigned int size;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int offBits;

    [[nodiscard]] unsigned int headerSize() const {
        return sizeof(type) +
               sizeof(size) +
               sizeof(reserved1) +
               sizeof(reserved2) +
               sizeof(offBits);
    }

    void clear() {
        memset(this, 0x00, sizeof(BITMAP_FILE_HEADER));
    }
};

struct BITMAP_INFO_HEADER {
    unsigned int size;
    unsigned int width;
    unsigned int height;
    unsigned short planes;
    unsigned short bitCount;
    unsigned int compression;
    unsigned int bufferSize;
    unsigned int xPelsPerMeter;
    unsigned int yPelsPerMeter;
    unsigned int usedColor;
    unsigned int importantColor;

    [[nodiscard]] unsigned int headerSize() const {
        return sizeof(size) +
               sizeof(width) +
               sizeof(height) +
               sizeof(planes) +
               sizeof(bitCount) +
               sizeof(compression) +
               sizeof(bufferSize) +
               sizeof(xPelsPerMeter) +
               sizeof(yPelsPerMeter) +
               sizeof(usedColor) +
               sizeof(importantColor);
    }

    void clear() {
        memset(this, 0x00, sizeof(BITMAP_INFO_HEADER));
    }
};

bool IsBigEndian();
unsigned short flipValue(const unsigned short& nValue);
unsigned int flipValue(const unsigned int& nValue);
void ReadBitmapFile(ifstream& pStream, BITMAP_FILE_HEADER& pHeader);
void ReadBitmapInfo(ifstream& pStream, BITMAP_INFO_HEADER& pHeader);
void WriteBitmapFile(ofstream& pStream, BITMAP_FILE_HEADER& pHeader);
void WriteBitmapInfo(ifstream& pStream, BITMAP_INFO_HEADER& pHeader);

#endif //YOONIMAGE_BITMAP_H
