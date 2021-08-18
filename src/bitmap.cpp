//
// Created by 윤철중 on 2021/08/18.
//
#include "bitmap.h"

// Save the MSB(Most Significant Bit) first
bool IsBigEndian() {
    unsigned int nValue = 0x01;
    return (1 != reinterpret_cast<char *>(&nValue)[0]); // RISC CPU
}

unsigned short flipValue(const unsigned short& nValue) {
    return ((nValue >> 8) || (nValue << 8));
}

unsigned int flipValue(const unsigned int& nValue) {
    return (
            ((nValue & 0xFF000000) >> 0x18) |
            ((nValue & 0x000000FF) << 0x18) |
            ((nValue & 0x00FF0000) >> 0x08) |
            ((nValue & 0x0000FF00) << 0x08)
    );
}

template <typename T>
void ReadStream(ifstream& pStream, T& value) {
    pStream.read(reinterpret_cast<char *>(&value), sizeof(T));
}

template <typename T>
void WriteStream(ofstream& pStream, const T& value)  {
    pStream.write(reinterpret_cast<const char*>(&value), sizeof(T));
}

void ReadBitmapFileHeader(ifstream& pStream, BITMAP_FILE_HEADER& pHeader) {
    ReadStream(pStream, pHeader.type);
    ReadStream(pStream, pHeader.size);
    ReadStream(pStream, pHeader.reserved1);
    ReadStream(pStream, pHeader.reserved2);
    ReadStream(pStream, pHeader.offBits);
    if (IsBigEndian()) {
        pHeader.type = flipValue(pHeader.type);
        pHeader.size = flipValue(pHeader.size);
        pHeader.reserved1 = flipValue(pHeader.reserved1);
        pHeader.reserved2 = flipValue(pHeader.reserved2);
        pHeader.offBits = flipValue(pHeader.offBits);
    }
}

void ReadBitmapInfoHeader(ifstream& pStream, BITMAP_INFO_HEADER& pHeader) {
    ReadStream(pStream, pHeader.size);
    ReadStream(pStream, pHeader.width);
    ReadStream(pStream, pHeader.height);
    ReadStream(pStream, pHeader.planes);
    ReadStream(pStream, pHeader.bitCount);
    ReadStream(pStream, pHeader.compression);
    ReadStream(pStream, pHeader.bufferSize);
    ReadStream(pStream, pHeader.xPelsPerMeter);
    ReadStream(pStream, pHeader.yPelsPerMeter);
    ReadStream(pStream, pHeader.usedColor);
    ReadStream(pStream, pHeader.importantColor);
    if (IsBigEndian()) {
        pHeader.size = flipValue(pHeader.size);
        pHeader.width = flipValue(pHeader.width);
        pHeader.height = flipValue(pHeader.height);
        pHeader.planes = flipValue(pHeader.planes);
        pHeader.bitCount = flipValue(pHeader.bitCount);
        pHeader.compression = flipValue(pHeader.compression);
        pHeader.bufferSize = flipValue(pHeader.bufferSize);
        pHeader.xPelsPerMeter = flipValue(pHeader.xPelsPerMeter);
        pHeader.yPelsPerMeter = flipValue(pHeader.yPelsPerMeter);
        pHeader.usedColor = flipValue(pHeader.usedColor);
        pHeader.importantColor = flipValue(pHeader.importantColor);
    }
}

void WriteBitmapFileHeader(ofstream& pStream, BITMAP_FILE_HEADER& pHeader) {
    if (IsBigEndian()) {
        WriteStream(pStream, flipValue(pHeader.type));
        WriteStream(pStream, flipValue(pHeader.size));
        WriteStream(pStream, flipValue(pHeader.reserved1));
        WriteStream(pStream, flipValue(pHeader.reserved2));
        WriteStream(pStream, flipValue(pHeader.offBits));
    } else {
        WriteStream(pStream, pHeader.type);
        WriteStream(pStream, pHeader.size);
        WriteStream(pStream, pHeader.reserved1);
        WriteStream(pStream, pHeader.reserved2);
        WriteStream(pStream, pHeader.offBits);
    }
}

void WriteBitmapInfo(ofstream& pStream, BITMAP_INFO_HEADER& pHeader) {
    if (IsBigEndian()) {
        WriteStream(pStream, flipValue(pHeader.size));
        WriteStream(pStream, flipValue(pHeader.width));
        WriteStream(pStream, flipValue(pHeader.height));
        WriteStream(pStream, flipValue(pHeader.planes));
        WriteStream(pStream, flipValue(pHeader.bitCount));
        WriteStream(pStream, flipValue(pHeader.compression));
        WriteStream(pStream, flipValue(pHeader.bufferSize));
        WriteStream(pStream, flipValue(pHeader.xPelsPerMeter));
        WriteStream(pStream, flipValue(pHeader.yPelsPerMeter));
        WriteStream(pStream, flipValue(pHeader.usedColor));
        WriteStream(pStream, flipValue(pHeader.importantColor));
    } else {
        WriteStream(pStream, pHeader.size);
        WriteStream(pStream, pHeader.width);
        WriteStream(pStream, pHeader.height);
        WriteStream(pStream, pHeader.planes);
        WriteStream(pStream, pHeader.bitCount);
        WriteStream(pStream, pHeader.compression);
        WriteStream(pStream, pHeader.bufferSize);
        WriteStream(pStream, pHeader.xPelsPerMeter);
        WriteStream(pStream, pHeader.yPelsPerMeter);
        WriteStream(pStream, pHeader.usedColor);
        WriteStream(pStream, pHeader.importantColor);
    }
}