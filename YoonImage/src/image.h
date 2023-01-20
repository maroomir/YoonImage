//
// Created by maroomir on 2021-07-05.
//

#ifndef YOONIMAGE_IMAGE_H
#define YOONIMAGE_IMAGE_H

#include "enums.h"
#include "bitmap_factory.h"
#include <string>

using namespace std;

#define IMAGE_DEFAULT_CHANNEL 1
#define IMAGE_DEFAULT_WIDTH 640
#define IMAGE_DEFAULT_HEIGHT 480

class Image {
private:
    static int ToChannel(eImageFormat eFormat);
    static eImageFormat ToImageFormat(int nChannel);
    static unsigned char* ToByte(const int& nNumber);
    static int ToInteger(const unsigned char* pByte);
    unsigned char* ToMixedColorBuffer(const unsigned char* pParallelBuffer, bool bReverseOrder);
    unsigned char* ToParallelColorBuffer(const unsigned char* pMixedBuffer, bool bOrderRGB);

private:
    unsigned char *m_pBuffer;  // "Gray" or Parallel Color Buffers (R + G + B)
    int m_nWidth, m_nHeight, m_nChannel;
    eImageFormat m_eFormat;

public:
    Image();
    ~Image();
    Image(const Image &pImage);
    Image(const string& strImagePath);
    Image(int nWidth, int nHeight, int nChannel);
    Image(int *pBuffer, int nWidth, int nHeight);
    Image(unsigned char *pRedBuffer, unsigned char *pGreenBuffer, unsigned char *pBlueBuffer, int nWidth, int nHeight);
    Image(unsigned char *pBuffer, int nWidth, int nHeight, eImageFormat eFormat);

    int Width();
    int Height();
    int Channel();
    int Stride();
    unsigned char* GetBuffer();
    unsigned char* CopyBuffer();
    unsigned char* GetMixedColorBuffer();
    eImageFormat ImageFormat();

    Image* ToGrayImage();
    Image* ToRedImage();
    Image* ToGreenImage();
    Image* ToBlueImage();
    unsigned char* ToGrayBuffer();
    unsigned char* ToRedBuffer();
    unsigned char* ToGreenBuffer();
    unsigned char* ToBlueBuffer();

    void CopyFrom(const Image &pImage);
    Image* Clone();
    bool Equals(const Image &pImage);
    bool LoadBitmap(const string& strPath);
    bool SaveBitmap(const string& strPath);

public:
    static Image* GrayPaletteBar();
    static Image* ColorPaletteBar();
};


#endif //YOONIMAGE_IMAGE_H
