//
// Created by maroomir on 2021-07-05.
//

#ifndef YOONIMAGE_IMAGE_H
#define YOONIMAGE_IMAGE_H

#include "enum.h"
#include <string>

using namespace std;

#define IMAGE_DEFAULT_CHANNEL 1
#define IMAGE_DEFAULT_WIDTH 640
#define IMAGE_DEFAULT_HEIGHT 480

class YoonImage {
private:
    static int GetChannelFromFormat(eYoonImageFormat eFormat);
    static eYoonImageFormat GetFormatFromChannel(int nChannel);
    static unsigned char* ConvertByte(const int& nNumber);
    static int ConvertInteger(const unsigned char* pByte);

private:
    unsigned char *m_pBuffer;
    int m_nWidth, m_nHeight, m_nChannel;
    eYoonImageFormat m_eFormat;

public:
    YoonImage();
    ~YoonImage();
    YoonImage(const YoonImage &pImage);
    YoonImage(int nWidth, int nHeight, int nChannel);
    YoonImage(const int *m_pBuffer, int nWidth, int nHeight);
    YoonImage(unsigned char *m_pBuffer, int nWidth, int nHeight, eYoonImageFormat eFormat);
    YoonImage(void *pAddress, short nWidth, short nHeight, eYoonImageFormat eFormat);

    int GetWidth();
    int GetHeight();
    int GetPlane();
    int GetStride();
    unsigned char* GetBuffer();
    eYoonImageFormat GetImageFormat();

    void CopyFrom(const YoonImage &pImage);
    YoonImage Clone();
    bool Equals(const YoonImage &pImage);
    bool LoadImage(string strImagePath);
    bool SaveImage(string strImagePath);
};


#endif //YOONIMAGE_IMAGE_H
