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

void ReadBitmapFile(ifstream& pStream, BITMAP_FILE_HEADER& pHeader) {
    pStream.read(reinterpret_cast<char *>(&pHeader.type), sizeof(short));
    pStream.read(reinterpret_cast<char *>(&pHeader.size), sizeof(int));
    pStream.read(reinterpret_cast<char *>(&pHeader.reserved1), sizeof(short));
    pStream.read(reinterpret_cast<char *>(&pHeader.reserved2), sizeof(short));
    pStream.read(reinterpret_cast<char *>(&pHeader.offBits), sizeof(int));
    if (IsBigEndian()) {
        pHeader.type = flipValue(pHeader.type);
        pHeader.size = flipValue(pHeader.size);
        pHeader.reserved1 = flipValue(pHeader.reserved1);
        pHeader.reserved2 = flipValue(pHeader.reserved2);
        pHeader.offBits = flipValue(pHeader.offBits);
    }
}

void ReadBitmapInfo(ifstream& pStream, BITMAP_INFO_HEADER& pHeader);
void WriteBitmapFile(ofstream& pStream, BITMAP_FILE_HEADER& pHeader);
void WriteBitmapInfo(ifstream& pStream, BITMAP_INFO_HEADER& pHeader);