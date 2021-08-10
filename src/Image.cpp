//
// Created by maroomir on 2021-07-05.
//

#include "Image.h"

YoonImage::YoonImage() {
    m_nWidth = IMAGE_DEFAULT_WIDTH;
    m_nHeight = IMAGE_DEFAULT_HEIGHT;
    m_nChannel = IMAGE_DEFAULT_CHANNEL;
    m_eFormat = GetFormatFromChannel(m_nChannel);
    m_pBuffer = (unsigned char *) malloc(sizeof(char) * m_nWidth * m_nHeight * m_nChannel);
    memset(m_pBuffer, 0, sizeof(char) * m_nWidth * m_nHeight);
}

YoonImage::YoonImage(const YoonImage &pImage) {
    m_nWidth = pImage.m_nWidth;
    m_nHeight = pImage.m_nHeight;
    m_nChannel = pImage.m_nChannel;
    m_eFormat = pImage.m_eFormat;
    m_pBuffer = (unsigned char *) malloc(sizeof(char) * m_nWidth * m_nHeight * m_nChannel);
    memcpy(m_pBuffer, pImage.m_pBuffer, sizeof(char) * m_nWidth * m_nHeight * m_nChannel);
}

YoonImage::YoonImage(int nWidth, int nHeight, int nChannel) {
    m_nWidth = nWidth;
    m_nHeight = nHeight;
    m_nChannel = nChannel;
    m_eFormat = GetFormatFromChannel(m_nChannel);
    m_pBuffer = (unsigned char *) malloc(sizeof(char) * m_nWidth * m_nHeight * m_nChannel);
    memset(m_pBuffer, 0, sizeof(char) * m_nWidth * m_nHeight * m_nChannel);
}

YoonImage::YoonImage(int* pBuffer, int nWidth, int nHeight) {
    m_nWidth = nWidth;
    m_nHeight = nHeight;
    m_nChannel = 3;
    m_eFormat = GetFormatFromChannel(m_nChannel);
    m_pBuffer = (unsigned char *) malloc(sizeof(char) * m_nWidth * m_nHeight * m_nChannel);
    for (int i = 0; i < nWidth * nHeight; i++) {
        unsigned char *pByte = ConvertByte(pBuffer[i]);
        memcpy(m_pBuffer + i * m_nChannel, pByte, sizeof(char) * m_nChannel);
        delete pByte;
    }
}

YoonImage::YoonImage(unsigned char *pBuffer, int nWidth, int nHeight, eYoonImageFormat eFormat) {
    m_nWidth = nWidth;
    m_nHeight = nHeight;
    m_eFormat = eFormat;
    m_nChannel = GetChannelFromFormat(m_eFormat);
    pBuffer = (unsigned char *) malloc(sizeof(char) * m_nWidth * m_nHeight * m_nChannel);
    switch (m_eFormat) {
        case FORMAT_GRAY:
            memcpy(m_pBuffer, pBuffer, sizeof(char) * m_nWidth * m_nHeight * m_nChannel);
            break;
        case FORMAT_RGB:
        case FORMAT_RGB_MIXED:
            for (int i = 0; i < nWidth * nHeight; i++) {
                //
            }
    }
}

YoonImage::~YoonImage() {
    if (m_pBuffer != nullptr) {
        free(m_pBuffer);
    }
}

int YoonImage::GetChannelFromFormat(eYoonImageFormat eFormat) {
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
            break;
    }
    return nChannel;
}

eYoonImageFormat YoonImage::GetFormatFromChannel(int nChannel) {
    eYoonImageFormat eFormat = FORMAT_NONE;
    switch (nChannel) {
        case 1:
            eFormat = FORMAT_GRAY;
            break;
        case 3:
            eFormat = FORMAT_RGB;
            break;
        default:
            break;
    }
    return eFormat;
}

unsigned char* YoonImage::ConvertByte(const int &nNumber) {
    auto* pByte = new unsigned char[4];
    pByte[0] = (nNumber & 0x000000ff);
    pByte[1] = (nNumber & 0x0000ff00) >> 8;
    pByte[2] = (nNumber & 0x00ff0000) >> 16;
    pByte[3] = (nNumber & 0xff000000) >> 24;
    return pByte;
}

int YoonImage::ConvertInteger(const unsigned char *pByte) {
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