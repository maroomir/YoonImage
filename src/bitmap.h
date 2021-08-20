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

struct BITMAP_PALETTE {
    unsigned char blue;
    unsigned char green;
    unsigned char red;
    unsigned char reserved;
};

class BitmapFactory {
private:
    static bool IsBigEndian();

    static unsigned short flipOrder(const unsigned short &nValue);

    static unsigned int flipOrder(const unsigned int &nValue);

    static size_t GetFileSize(const string &strPath);

    template<typename T>
    static void ReadStream(ifstream &pStream, T &value);

    template<typename T>
    static void WriteStream(ofstream &pStream, const T &value);

public:
    static void ReadBitmapFileHeader(ifstream &pStream, BITMAP_FILE_HEADER &pHeader);

    static void ReadBitmapInfoHeader(ifstream &pStream, BITMAP_INFO_HEADER &pHeader);

    static void WriteBitmapFileHeader(ofstream &pStream, BITMAP_FILE_HEADER &pHeader);

    static void WriteBitmapInfoHeader(ofstream &pStream, BITMAP_INFO_HEADER &pHeader);

    static void WriteBitmapPaletteTable(ofstream &pStream);

    static BITMAP_PALETTE * ReadBitmapPaletteTable(ifstream &pStream);

    static void
    WriteBitmapBuffer(ofstream &pStream, unsigned char *pBuffer, int nWidth, int nHeight, int nChannel);

    static unsigned char *
    ReadBitmapBuffer(ifstream &pStream, const string &strPath, int nWidth, int nHeight, int nChannel);
};


#endif //YOONIMAGE_BITMAP_H
