//
// Created by maroomir on 2021-07-05.
//

#ifndef YOONIMAGE_IMAGE_H
#define YOONIMAGE_IMAGE_H

#include "enum.h"
#include "bitmap.h"
#include <string>

using namespace std;

#define IMAGE_DEFAULT_CHANNEL 1
#define IMAGE_DEFAULT_WIDTH 640
#define IMAGE_DEFAULT_HEIGHT 480

class YoonImage {
private:
    static int ToChannel(eYoonImageFormat eFormat);
    static eYoonImageFormat ToImageFormat(int nChannel);
    static unsigned char* ToByte(const int& nNumber);
    static int ToInteger(const unsigned char* pByte);
    unsigned char* ToMixedColorBuffer(const unsigned char* pParallelBuffer, bool bReverseOrder);
    unsigned char* ToParallelColorBuffer(const unsigned char* pMixedBuffer, bool bOrderRGB);

private:
    unsigned char *m_pBuffer;  // "Gray" or Parallel Color Buffers (R + G + B)
    int m_nWidth, m_nHeight, m_nChannel;
    eYoonImageFormat m_eFormat;

public:
    YoonImage();
    ~YoonImage();
    YoonImage(const YoonImage &pImage);
    YoonImage(const string& strImagePath);
    YoonImage(int nWidth, int nHeight, int nChannel);
    YoonImage(int *pBuffer, int nWidth, int nHeight);
    YoonImage(unsigned char *pBuffer, int nWidth, int nHeight, eYoonImageFormat eFormat);

    int GetWidth();
    int GetHeight();
    int GetChannel();
    int GetStride();
    unsigned char* GetBuffer();
    unsigned char* CopyBuffer();
    unsigned char* GetMixedColorBuffer();
    eYoonImageFormat GetImageFormat();

    YoonImage* ToGrayImage();
    YoonImage* ToRedImage();
    YoonImage* ToGreenImage();
    YoonImage* ToBlueImage();
    unsigned char* ToGrayBuffer();
    unsigned char* ToRedBuffer();
    unsigned char* ToGreenBuffer();
    unsigned char* ToBlueBuffer();

    void CopyFrom(const YoonImage &pImage);
    YoonImage* Clone();
    bool Equals(const YoonImage &pImage);
    bool LoadBitmap(const string& strPath);
    bool SaveBitmap(const string& strPath);
};


#endif //YOONIMAGE_IMAGE_H
