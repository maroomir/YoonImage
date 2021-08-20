//
// Created by maroomir on 2021-07-05.
//

#include "Image.h"
#include <fstream>
#include <iostream>

YoonImage::YoonImage() {
    m_nWidth = IMAGE_DEFAULT_WIDTH;
    m_nHeight = IMAGE_DEFAULT_HEIGHT;
    m_nChannel = IMAGE_DEFAULT_CHANNEL;
    m_eFormat = ToImageFormat(m_nChannel);
    m_pBuffer = static_cast<unsigned char *>(malloc(sizeof(char) * m_nWidth * m_nHeight * m_nChannel));
    memset(m_pBuffer, 0, sizeof(char) * m_nWidth * m_nHeight);
}

YoonImage::YoonImage(const YoonImage &pImage) {
    m_nWidth = pImage.m_nWidth;
    m_nHeight = pImage.m_nHeight;
    m_nChannel = pImage.m_nChannel;
    m_eFormat = pImage.m_eFormat;
    m_pBuffer = static_cast<unsigned char *>(malloc(sizeof(char) * m_nWidth * m_nHeight * m_nChannel));
    memcpy(m_pBuffer, pImage.m_pBuffer, sizeof(char) * m_nWidth * m_nHeight * m_nChannel);
}


YoonImage::YoonImage(const string &strImagePath) {
    LoadBitmap(strImagePath);
}

YoonImage::YoonImage(int nWidth, int nHeight, int nChannel) {
    m_nWidth = nWidth;
    m_nHeight = nHeight;
    m_nChannel = nChannel;
    m_eFormat = ToImageFormat(m_nChannel);
    m_pBuffer = static_cast<unsigned char *>(malloc(sizeof(char) * m_nWidth * m_nHeight * m_nChannel));
    memset(m_pBuffer, 0, sizeof(char) * m_nWidth * m_nHeight * m_nChannel);
}

YoonImage::YoonImage(int* pBuffer, int nWidth, int nHeight) {
    m_nWidth = nWidth;
    m_nHeight = nHeight;
    m_nChannel = 3;
    m_eFormat = ToImageFormat(m_nChannel);
    m_pBuffer = static_cast<unsigned char *>(malloc(sizeof(char) * m_nWidth * m_nHeight * m_nChannel));
    for (int i = 0; i < nWidth * nHeight; i++) {
        unsigned char *pByte = ToByte(pBuffer[i]);
        memcpy(m_pBuffer + i * m_nChannel * sizeof(char), pByte, sizeof(char) * m_nChannel);
        delete pByte;
    }
}

YoonImage::YoonImage(unsigned char *pBuffer, int nWidth, int nHeight, eYoonImageFormat eFormat) {
    m_nWidth = nWidth;
    m_nHeight = nHeight;
    m_nChannel = ToChannel(eFormat);
    switch (eFormat) {
        case FORMAT_GRAY:
            m_eFormat = FORMAT_GRAY;
            m_pBuffer = static_cast<unsigned char *>(malloc(sizeof(char) * m_nWidth * m_nHeight * m_nChannel));
            memcpy(m_pBuffer, pBuffer, sizeof(char) * m_nWidth * m_nHeight * m_nChannel);
            break;
        case FORMAT_RGB:
        case FORMAT_RGB_PARALLEL:
            m_eFormat = FORMAT_RGB;
            m_pBuffer = static_cast<unsigned char *>(malloc(sizeof(char) * m_nWidth * m_nHeight * m_nChannel));
            memcpy(m_pBuffer, pBuffer, sizeof(char) * m_nWidth * m_nHeight * m_nChannel);
            break;
        case FORMAT_RGB_MIXED:  // Separate the pixel to Red, Green, Blue buffers
            m_eFormat = FORMAT_RGB;
            m_pBuffer = ToParallelColorBuffer(pBuffer, false);
            break;
        case FORMAT_BGR:
        case FORMAT_BGR_PARALLEL:
            m_eFormat = FORMAT_RGB;
            m_pBuffer = static_cast<unsigned char *>(malloc(sizeof(char) * m_nWidth * m_nHeight * m_nChannel));
            for(int iColor = 0; iColor < m_nChannel; iColor++)
            {
                int nStart = (m_nChannel - iColor - 1) * m_nWidth * m_nHeight;
                memcpy(m_pBuffer, pBuffer + sizeof(char) * nStart, sizeof(char) * m_nWidth * m_nHeight);
            }
            break;
        case FORMAT_BGR_MIXED:
            m_eFormat = FORMAT_RGB;
            m_pBuffer = ToParallelColorBuffer(pBuffer, true);
            break;
        default:
            std::printf("[YOONIMAGE] Abnormal Image Format");
            m_eFormat = FORMAT_GRAY;
            m_pBuffer = static_cast<unsigned char *>(malloc(sizeof(char) * m_nWidth * m_nHeight * m_nChannel));
            memset(m_pBuffer, 0, sizeof(char) * m_nWidth * m_nHeight * m_nChannel);
            break;
    }
}

YoonImage::~YoonImage() {
    if (!m_pBuffer) {
        free(m_pBuffer);
        m_pBuffer = nullptr;
    }
}

int YoonImage::ToChannel(eYoonImageFormat eFormat) {
    int nChannel = INVALID_INTEGER;
    switch (eFormat) {
        case FORMAT_GRAY:
            nChannel = 1;
            break;
        case FORMAT_RGB:
        case FORMAT_RGB_PARALLEL:
        case FORMAT_RGB_MIXED:
        case FORMAT_BGR:
        case FORMAT_BGR_PARALLEL:
        case FORMAT_BGR_MIXED:
            nChannel = 3;
            break;
        default:
            std::printf("[YOONIMAGE][ToChannel] Abnormal Image Format");
            break;
    }
    return nChannel;
}

eYoonImageFormat YoonImage::ToImageFormat(int nChannel) {
    eYoonImageFormat eFormat = FORMAT_NONE;
    switch (nChannel) {
        case 1:
            eFormat = FORMAT_GRAY;
            break;
        case 3:
            eFormat = FORMAT_RGB;
            break;
        default:
            std::printf("[YOONIMAGE][ToImageFormat] Abnormal Image Channel");
            break;
    }
    return eFormat;
}

unsigned char* YoonImage::ToByte(const int &nNumber) {
    auto* pByte = new unsigned char[4];
    pByte[0] = (nNumber & 0x000000ff);
    pByte[1] = (nNumber & 0x0000ff00) >> 8;
    pByte[2] = (nNumber & 0x00ff0000) >> 16;
    pByte[3] = (nNumber & 0xff000000) >> 24;
    return pByte;
}

int YoonImage::ToInteger(const unsigned char *pByte) {
    int nNumber = INVALID_INTEGER;
    int nLength = sizeof(pByte) / sizeof(char);
    if (pByte != nullptr && nLength >= 4) {
        nNumber += (pByte[0] & 0x000000ff);
        nNumber += (pByte[1] & 0x000000ff) << 8;
        nNumber += (pByte[2] & 0x000000ff) << 16;
        nNumber += (pByte[3] & 0x000000ff) << 24;
    }
    return nNumber;
}

unsigned char* YoonImage::ToParallelColorBuffer(const unsigned char *pMixedBuffer, bool bReverseOrder) {
    unsigned char *pResultBuffer = static_cast<unsigned char *>(malloc(
            sizeof(char) * m_nWidth * m_nHeight * m_nChannel));
    for (int iColor = 0; iColor < m_nChannel; iColor++) {
        int nStart = iColor * m_nWidth * m_nHeight;
        int nColor = (bReverseOrder) ? m_nChannel - iColor - 1 : iColor;  // BRG or RGB
        for (int iY = 0; iY < m_nHeight; iY++) {
            for (int iX = 0; iX < m_nWidth; iX++) {
                pResultBuffer[nStart + iY * m_nWidth + iX] = pMixedBuffer[iY * m_nWidth * m_nChannel + iX * m_nChannel + nColor];
            }
        }
    }
    return pResultBuffer;
}

unsigned char* YoonImage::ToMixedColorBuffer(const unsigned char *pParallelBuffer, bool bReverseOrder) {
    unsigned char *pResultBuffer = static_cast<unsigned char *>(malloc(
            sizeof(char) * m_nWidth * m_nHeight * m_nChannel));

    for (int iColor = 0; iColor < m_nChannel; iColor++) {
        int nStart = iColor * m_nWidth * m_nHeight;
        int nColor = (bReverseOrder) ? m_nChannel - iColor - 1 : iColor;
        for (int iY = 0; iY < m_nHeight; iY++) {
            for (int iX = 0; iX < m_nWidth; iX++) {
                pResultBuffer[iY * m_nWidth * m_nChannel + iX * m_nChannel + nColor] = pParallelBuffer[nStart + iY * m_nWidth + iX];
            }
        }
    }
    return pResultBuffer;
}

int YoonImage::GetWidth() {
    return m_nWidth;
}

int YoonImage::GetHeight() {
    return m_nHeight;
}

int YoonImage::GetChannel() {
    return m_nChannel;
}

int YoonImage::GetStride() {
    return m_nWidth * m_nChannel;
}

unsigned char* YoonImage::GetBuffer() {
    return m_pBuffer;
}

unsigned char* YoonImage::CopyBuffer() {
    auto* pBuffer = static_cast<unsigned char *>(malloc(sizeof(char) * m_nWidth * m_nHeight * m_nChannel));
    memcpy(pBuffer, m_pBuffer, sizeof(char) * m_nWidth * m_nHeight * m_nChannel);
    return pBuffer;
}

eYoonImageFormat YoonImage::GetImageFormat() {
    return m_eFormat;
}

unsigned char* YoonImage::GetMixedColorBuffer() {
    unsigned char *pBuffer = nullptr;
    switch (m_eFormat) {
        case FORMAT_GRAY: {
            int nSize = m_nWidth * m_nHeight;
            pBuffer = static_cast<unsigned char *>(malloc(sizeof(char) * nSize * 3));
            for (int iColor = 0; iColor < 3; iColor++) {
                int nOffset = nSize * iColor;
                memcpy(pBuffer + sizeof(char) * nOffset, m_pBuffer + sizeof(char) * nOffset, sizeof(char) * nSize);
            }
            break;
        }
        case FORMAT_RGB:
            pBuffer = ToMixedColorBuffer(m_pBuffer, true);
            break;
        case FORMAT_BGR:
            pBuffer = ToMixedColorBuffer(m_pBuffer, false);
            break;
        default:
            std::printf("[YOONIMAGE][GetMixedColorBuffer] Abnormal Image Format");
            break;
    }
    return pBuffer;
}

void YoonImage::CopyFrom(const YoonImage &pImage) {
    m_nWidth = pImage.m_nWidth;
    m_nHeight = pImage.m_nHeight;
    m_nChannel = pImage.m_nChannel;
    m_eFormat = pImage.m_eFormat;
    if(m_pBuffer != nullptr)
    {
        free(m_pBuffer);
        m_pBuffer = nullptr;
    }
    m_pBuffer = static_cast<unsigned char *>(malloc(sizeof(char) * m_nWidth * m_nHeight * m_nChannel));
    memcpy(m_pBuffer, pImage.m_pBuffer, sizeof(char)*m_nWidth*m_nHeight*m_nChannel);
}

YoonImage* YoonImage::Clone() {
    return new YoonImage(m_pBuffer, m_nWidth, m_nHeight, m_eFormat);
}

bool YoonImage::Equals(const YoonImage &pImage) {
    bool bEqual = (m_nWidth == pImage.m_nWidth) &&
            (m_nHeight == pImage.m_nHeight) &&
            (m_nChannel == pImage.m_nChannel) &&
            (m_eFormat == pImage.m_eFormat);
    if(bEqual)
    {
        int nSize = m_nWidth * m_nHeight * m_nChannel;
        for(int i=0; i<nSize; i++)
        {
            if(m_pBuffer[i] != pImage.m_pBuffer[i])
            {
                bEqual = false;
                break;
            }
        }
    }
    return bEqual;
}

unsigned char* YoonImage::ToGrayBuffer() {
    int nSize = m_nWidth * m_nHeight;
    auto *pResultBuffer = new unsigned char[sizeof(char) * nSize];
    switch (m_eFormat) {
        case FORMAT_GRAY:
            memcpy(pResultBuffer, m_pBuffer, sizeof(char) * nSize);
            break;
        case FORMAT_RGB:
            for (int iHeight = 0; iHeight < m_nHeight; iHeight++) {
                for (int iWidth = 0; iWidth < m_nWidth; iWidth++) {
                    int nPos = iHeight * m_nWidth + iWidth;
                    unsigned char pRed = m_pBuffer[nPos];
                    unsigned char pGreen = m_pBuffer[nSize + nPos];
                    unsigned char pBlue = m_pBuffer[2 * nSize + nPos];
                    // ITU-RBT.709, YPrPb
                    pResultBuffer[nPos] = (unsigned char) (0.299 * pRed + 0.587 * pGreen + 0.114 * pBlue);
                }
            }
            break;
        case FORMAT_BGR:
            for (int iHeight = 0; iHeight < m_nHeight; iHeight++) {
                for (int iWidth = 0; iWidth < m_nWidth; iWidth++) {
                    int nPos = iHeight * m_nWidth + iWidth;
                    unsigned char pBlue = m_pBuffer[nPos];
                    unsigned char pGreen = m_pBuffer[nSize + nPos];
                    unsigned char pRed = m_pBuffer[2 * nSize + nPos];
                    // ITU-RBT.709, YPrPb
                    pResultBuffer[nPos] = (unsigned char) (0.299 * pRed + 0.587 * pGreen + 0.114 * pBlue);
                }
            }
            break;
        default:
            std::printf("[YOONIMAGE][ToGrayImage] Abnormal Image Format");
            memset(pResultBuffer, 0, sizeof(char) * nSize);
            break;
    }
    return pResultBuffer;
}

YoonImage* YoonImage::ToGrayImage() {
    unsigned char *pResultBuffer = ToGrayBuffer();
    auto *pResultImage = new YoonImage(pResultBuffer, m_nWidth, m_nHeight, FORMAT_GRAY);
    delete[] pResultBuffer;
    return pResultImage;
}

unsigned char* YoonImage::ToRedBuffer() {
    int nSize = m_nWidth * m_nHeight;
    auto *pResultBuffer = new unsigned char[sizeof(char) * nSize];
    switch (m_eFormat) {
        case FORMAT_GRAY:
        case FORMAT_RGB:  // "R" G B
            memcpy(pResultBuffer, m_pBuffer, sizeof(char) * nSize);
            break;
        case FORMAT_BGR:  // B G "R"
            memcpy(pResultBuffer, m_pBuffer + sizeof(char) * nSize * 2, sizeof(char) * nSize);
            break;
        default:
            std::printf("[YOONIMAGE][ToRedImage] Abnormal Image Format");
            memset(pResultBuffer, 0, sizeof(char) * nSize);
            break;
    }
    return pResultBuffer;
}

YoonImage* YoonImage::ToRedImage() {
    unsigned char *pResultBuffer = ToRedBuffer();
    auto *pResultImage = new YoonImage(pResultBuffer, m_nWidth, m_nHeight, FORMAT_GRAY);
    delete[] pResultBuffer;
    return pResultImage;
}

unsigned char* YoonImage::ToGreenBuffer() {
    int nSize = m_nWidth * m_nHeight;
    auto *pResultBuffer = new unsigned char[sizeof(char) * nSize];
    switch (m_eFormat) {
        case FORMAT_GRAY:
            memcpy(pResultBuffer, m_pBuffer, sizeof(char) * nSize);
            break;
        case FORMAT_RGB:  // R "G" B
        case FORMAT_BGR:  // B "G" R
            memcpy(pResultBuffer, m_pBuffer + sizeof(char) * nSize, sizeof(char) * nSize);
            break;
        default:
            std::printf("[YOONIMAGE][ToGreenImage] Abnormal Image Format");
            memset(pResultBuffer, 0, sizeof(char) * nSize);
            break;
    }
    return pResultBuffer;
}

YoonImage* YoonImage::ToGreenImage() {
    unsigned char* pResultBuffer = ToGreenBuffer();
    auto *pResultImage = new YoonImage(pResultBuffer, m_nWidth, m_nHeight, FORMAT_GRAY);
    delete[] pResultBuffer;
    return pResultImage;
}

unsigned char* YoonImage::ToBlueBuffer() {
    int nSize = m_nWidth * m_nHeight;
    auto *pResultBuffer = new unsigned char[sizeof(char) * nSize];
    switch (m_eFormat) {
        case FORMAT_GRAY:
        case FORMAT_BGR:  // "B" G R
            memcpy(pResultBuffer, m_pBuffer, sizeof(char) * nSize);
            break;
        case FORMAT_RGB:  // R G "B"
            memcpy(pResultBuffer, m_pBuffer + sizeof(char) * nSize * 2, sizeof(char) * nSize);
            break;
        default:
            std::printf("[YOONIMAGE][ToRedImage] Abnormal Image Format");
            memset(pResultBuffer, 0, sizeof(char) * nSize);
            break;
    }
    return pResultBuffer;
}

YoonImage* YoonImage::ToBlueImage() {
    unsigned char* pResultBuffer = ToBlueBuffer();
    auto *pResultImage = new YoonImage(pResultBuffer, m_nWidth, m_nHeight, FORMAT_GRAY);
    delete[] pResultBuffer;
    return pResultImage;
}

bool YoonImage::LoadBitmap(const string &strPath) {
    ifstream pStream(strPath.c_str(), ios::binary);
    if (!pStream) {
        std::printf("[YOONIMAGE][LoadBitmap] File Path is not correct");
        return false;
    }

    if (!m_pBuffer) {
        free(m_pBuffer);
        m_pBuffer = nullptr;
    }
    m_nWidth = 0;
    m_nHeight = 0;
    m_nChannel = 0;
    BITMAP_FILE_HEADER pFileHeader;
    BITMAP_INFO_HEADER pInfoHeader;
    pFileHeader.clear();
    pInfoHeader.clear();
    BitmapFactory::ReadBitmapFileHeader(pStream, pFileHeader);
    BitmapFactory::ReadBitmapInfoHeader(pStream, pInfoHeader);
    if (pInfoHeader.size != pInfoHeader.headerSize()) {
        std::printf("[YOONIMAGE][LoadBitmap] Invalid Bitmap Size");
        pFileHeader.clear();
        pInfoHeader.clear();
        pStream.close();
        // Initialize the buffer
        m_nWidth = IMAGE_DEFAULT_WIDTH;
        m_nHeight = IMAGE_DEFAULT_HEIGHT;
        m_nChannel = IMAGE_DEFAULT_CHANNEL;
        m_eFormat = ToImageFormat(m_nChannel);
        m_pBuffer = static_cast<unsigned char *>(malloc(sizeof(char) * m_nWidth * m_nHeight * m_nChannel));
        memset(m_pBuffer, 0, sizeof(char) * m_nWidth * m_nHeight);
        return false;
    }

    m_nWidth = pInfoHeader.width;
    m_nHeight = pInfoHeader.height;
    m_nChannel = pInfoHeader.bitCount >> 3;  // 0x00011000 => 0x00000011
    m_eFormat = ToImageFormat(m_nChannel);
    try {
        if (m_eFormat == FORMAT_GRAY)
            BitmapFactory::ReadBitmapPaletteTable(pStream);
        unsigned char *pBuffer = BitmapFactory::ReadBitmapBuffer(pStream, strPath, m_nWidth, m_nHeight, m_nChannel);
        m_pBuffer = ToParallelColorBuffer(pBuffer, true);
        delete[] pBuffer;
        pStream.close();
    }
    catch (int nCode) {
        std::printf("[YOONIMAGE][LoadBitmap] Buffer Reading Error");
        pFileHeader.clear();
        pInfoHeader.clear();
        pStream.close();
        // Initialize the buffer
        m_nWidth = IMAGE_DEFAULT_WIDTH;
        m_nHeight = IMAGE_DEFAULT_HEIGHT;
        m_nChannel = IMAGE_DEFAULT_CHANNEL;
        m_eFormat = ToImageFormat(m_nChannel);
        m_pBuffer = static_cast<unsigned char *>(malloc(sizeof(char) * m_nWidth * m_nHeight * m_nChannel));
        memset(m_pBuffer, 0, sizeof(char) * m_nWidth * m_nHeight);
        return false;
    }
    return true;
}

bool YoonImage::SaveBitmap(const string &strPath) {
    ofstream pStream(strPath.c_str(), ios::binary);
    if (!pStream) {
        std::printf("[YOONIMAGE][SaveBitmap] File Path is not correct");
        return false;
    }
    if (!m_pBuffer) {
        std::printf("[YOONIMAGE][SaveBitmap] Buffer is empty");
        return false;
    }

    BITMAP_INFO_HEADER pInfoHeader;
    pInfoHeader.width = m_nWidth;
    pInfoHeader.height = m_nHeight;
    pInfoHeader.bitCount = m_nChannel << 3;  // 0x00000011 => 0x00011000
    pInfoHeader.importantColor = 0;
    pInfoHeader.usedColor = 0;
    pInfoHeader.compression = 0;
    pInfoHeader.planes = 1;
    pInfoHeader.size = pInfoHeader.headerSize();
    pInfoHeader.xPelsPerMeter = 0;
    pInfoHeader.yPelsPerMeter = 0;
    pInfoHeader.bufferSize = (((pInfoHeader.width * m_nChannel) + 3) & 0x0000FFFC) * pInfoHeader.height;
    BITMAP_FILE_HEADER pFileHeader;
    pFileHeader.type = 19778;  // 0x4D42 (Static Number)
    pFileHeader.size = pFileHeader.headerSize() + pInfoHeader.headerSize() + pInfoHeader.bufferSize;
    pFileHeader.reserved1 = 0;
    pFileHeader.reserved2 = 0;
    pFileHeader.offBits = pInfoHeader.headerSize() + pFileHeader.headerSize();
    BitmapFactory::WriteBitmapFileHeader(pStream, pFileHeader);
    BitmapFactory::WriteBitmapInfoHeader(pStream, pInfoHeader);

    int nSize = m_nWidth * m_nHeight;
    unsigned char *pBufferSaved;
    switch (m_eFormat) {
        case FORMAT_GRAY:
            // Palette Table
            BitmapFactory::WriteBitmapPaletteTable(pStream);
            // Pixel Buffer
            pBufferSaved = new unsigned char[sizeof(char) * nSize];
            memcpy(pBufferSaved, m_pBuffer, sizeof(char) * nSize);
            break;
        case FORMAT_RGB:
        case FORMAT_RGB_PARALLEL:
            pBufferSaved = ToMixedColorBuffer(m_pBuffer, true);  // TO_BGR_MIXED
            break;
        case FORMAT_BGR:
        case FORMAT_BGR_PARALLEL:
            pBufferSaved = ToMixedColorBuffer(m_pBuffer, false);  // TO_BGR_MIXED
            break;
        case FORMAT_RGB_MIXED:
        case FORMAT_BGR_MIXED:
            pBufferSaved = new unsigned char[nSize * m_nChannel];
            memcpy(pBufferSaved, m_pBuffer, sizeof(char) * nSize * m_nChannel);
            break;
        default:
            pBufferSaved = new unsigned char[nSize * m_nChannel];
            memset(pBufferSaved, 0, sizeof(char) * nSize * m_nChannel);
            break;
    }
    BitmapFactory::WriteBitmapBuffer(pStream, pBufferSaved, m_nWidth, m_nHeight, m_nChannel);
    pStream.close();
    delete[] pBufferSaved;
    return true;
}
