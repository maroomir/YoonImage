//
// Created by 윤철중 on 2021/08/18.
//
#include "bitmap.h"

// Save the MSB(Most Significant Bit) first
bool BitmapFactory::IsBigEndian() {
    unsigned int nValue = 0x01;
    return (1 != reinterpret_cast<char *>(&nValue)[0]); // RISC CPU
}

unsigned short BitmapFactory::flipOrder(const unsigned short& nValue) {
    return ((nValue >> 8) || (nValue << 8));
}

unsigned int BitmapFactory::flipOrder(const unsigned int& nValue) {
    return (
            ((nValue & 0xFF000000) >> 0x18) |
            ((nValue & 0x000000FF) << 0x18) |
            ((nValue & 0x00FF0000) >> 0x08) |
            ((nValue & 0x0000FF00) << 0x08)
    );
}

size_t BitmapFactory::GetFileSize(const string &strPath) {
    ifstream pFile(strPath.c_str(), ios::in | ios::binary);
    if (!pFile) return 0;
    pFile.seekg(0, ios::end);
    return static_cast<size_t>(pFile.tellg());
}

template <typename T>
void BitmapFactory::ReadStream(ifstream& pStream, T& value) {
    pStream.read(reinterpret_cast<char *>(&value), sizeof(T));
}

template <typename T>
void BitmapFactory::WriteStream(ofstream& pStream, const T& value)  {
    pStream.write(reinterpret_cast<const char*>(&value), sizeof(T));
}

void BitmapFactory::ReadBitmapFileHeader(ifstream& pStream, BITMAP_FILE_HEADER& pHeader) {
    ReadStream(pStream, pHeader.type);
    ReadStream(pStream, pHeader.size);
    ReadStream(pStream, pHeader.reserved1);
    ReadStream(pStream, pHeader.reserved2);
    ReadStream(pStream, pHeader.offBits);
    if (IsBigEndian()) {
        pHeader.type = flipOrder(pHeader.type);
        pHeader.size = flipOrder(pHeader.size);
        pHeader.reserved1 = flipOrder(pHeader.reserved1);
        pHeader.reserved2 = flipOrder(pHeader.reserved2);
        pHeader.offBits = flipOrder(pHeader.offBits);
    }
}

void BitmapFactory::ReadBitmapInfoHeader(ifstream& pStream, BITMAP_INFO_HEADER& pHeader) {
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
        pHeader.size = flipOrder(pHeader.size);
        pHeader.width = flipOrder(pHeader.width);
        pHeader.height = flipOrder(pHeader.height);
        pHeader.planes = flipOrder(pHeader.planes);
        pHeader.bitCount = flipOrder(pHeader.bitCount);
        pHeader.compression = flipOrder(pHeader.compression);
        pHeader.bufferSize = flipOrder(pHeader.bufferSize);
        pHeader.xPelsPerMeter = flipOrder(pHeader.xPelsPerMeter);
        pHeader.yPelsPerMeter = flipOrder(pHeader.yPelsPerMeter);
        pHeader.usedColor = flipOrder(pHeader.usedColor);
        pHeader.importantColor = flipOrder(pHeader.importantColor);
    }
}

void BitmapFactory::WriteBitmapFileHeader(ofstream& pStream, BITMAP_FILE_HEADER& pHeader) {
    if (IsBigEndian()) {
        WriteStream(pStream, flipOrder(pHeader.type));
        WriteStream(pStream, flipOrder(pHeader.size));
        WriteStream(pStream, flipOrder(pHeader.reserved1));
        WriteStream(pStream, flipOrder(pHeader.reserved2));
        WriteStream(pStream, flipOrder(pHeader.offBits));
    } else {
        WriteStream(pStream, pHeader.type);
        WriteStream(pStream, pHeader.size);
        WriteStream(pStream, pHeader.reserved1);
        WriteStream(pStream, pHeader.reserved2);
        WriteStream(pStream, pHeader.offBits);
    }
}

void BitmapFactory::WriteBitmapInfoHeader(ofstream& pStream, BITMAP_INFO_HEADER& pHeader) {
    if (IsBigEndian()) {
        WriteStream(pStream, flipOrder(pHeader.size));
        WriteStream(pStream, flipOrder(pHeader.width));
        WriteStream(pStream, flipOrder(pHeader.height));
        WriteStream(pStream, flipOrder(pHeader.planes));
        WriteStream(pStream, flipOrder(pHeader.bitCount));
        WriteStream(pStream, flipOrder(pHeader.compression));
        WriteStream(pStream, flipOrder(pHeader.bufferSize));
        WriteStream(pStream, flipOrder(pHeader.xPelsPerMeter));
        WriteStream(pStream, flipOrder(pHeader.yPelsPerMeter));
        WriteStream(pStream, flipOrder(pHeader.usedColor));
        WriteStream(pStream, flipOrder(pHeader.importantColor));
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

void BitmapFactory::WriteBitmapBuffer(ofstream &pStream, const unsigned char *pBuffer, int nWidth, int nHeight,
                                      int nChannel) {
    int nPlane = nWidth * nChannel;
    unsigned int pPadding = (4 - ((3 * nWidth) % 4)) % 4;
    char pPadBuffer[4] = {0x00, 0x00, 0x00, 0x00};
    for (int iHeight = 0; iHeight < nHeight; ++iHeight) {
        int iStart = iHeight * nPlane;
        pStream.write(reinterpret_cast<const char *>(pBuffer + sizeof(char) * iStart), sizeof(char) * nPlane);
        pStream.write(pPadBuffer, pPadding);
    }
}

unsigned char *
BitmapFactory::ReadBitmapBuffer(ifstream &pStream, const string &strPath, int nInfoHeaderSize, int nFileHeaderSize,
                                int nWidth, int nHeight, int nChannel) {
    unsigned int pPadding = (4 - ((3 * nWidth) % 4)) % 4;
    char pPadBuffer[4] = {0x00, 0x00, 0x00, 0x00};
    size_t nPhysicalSize = GetFileSize(strPath);
    size_t nLogicalSize = (nWidth * nWidth * nChannel) +
                          (nHeight * pPadding) + nInfoHeaderSize + nFileHeaderSize;
    if(nPhysicalSize != nLogicalSize) {
        cerr << "Mismatch between logical and physical sizes of bitmap. "
             << "Logical: " << nLogicalSize << " "
             << "Physical: " << nPhysicalSize << std::endl;
        throw -1;
    }

    int nPlane = nWidth * nChannel;
    auto *pBuffer = new unsigned char[nPlane * nHeight];
    for (int iHeight = 0; iHeight < nHeight; ++iHeight) {
        int iStart = iHeight * nPlane;
        pStream.read(reinterpret_cast<char *>(pBuffer + sizeof(char) * iStart), sizeof(char) * nPlane);
        pStream.read(pPadBuffer, pPadding);
    }
}