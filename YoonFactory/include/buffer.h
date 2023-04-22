//
// Created by 윤철중 on 2023/01/20.
//

#ifndef YOONFACTORY_BUFFER_H
#define YOONFACTORY_BUFFER_H

#include "rect.h"
#include "vector.h"

#define YBUFFER_ERR_BUFFER "[YOONBUFFER] Abnormal buffer address"
#define YBUFFER_ERR_LEN "[YOONBUFFER] Abnormal buffer length"
#define YBUFFER_ERR_OUT_RANGE "[YOONBUFFER] Arguments are out of range"
#define YBUFFER_ERR_NULL "[YOONBUFFER] Source buffer is null"

struct IBuffer {
    virtual int Length() = 0;

    virtual void* GetAddress() = 0;

    virtual bool SetBuffer(void* pAddress, int length) = 0;

    virtual bool Equals(IBuffer &buffer) = 0;

    virtual void CopyFrom(IBuffer &buffer) = 0;
};

template <typename T>
class Buffer1D: public IBuffer {
private:
    T *_pBuffer = nullptr;
    int _length;

public:
    explicit Buffer1D(int length);

    ~Buffer1D();

    int Length() override;

    void *GetAddress() override;

    void GetBuffer(T *pBuffer, int *length);

    void CopyBuffer(T *pBuffer, int *length);

    void CopyBuffer(int start, int end, T *pBuffer);

    bool SetBuffer(void *pAddress, int length) override;

    bool SetBuffer(T *pBuffer, int start, int end);

    T Value(int pos);

    bool SetValue(T value, int pos);

    bool Equals(IBuffer &buffer) override;

    void CopyFrom(IBuffer &buffer) override;

    Buffer1D Clone();

    bool operator==(const Buffer1D<T> &other);

    bool operator!=(const Buffer1D<T> &other);

    T &operator[](int index);
};

template <typename T>
class Buffer2D: public IBuffer {
private:
    T* _pBuffer = nullptr;
    int _length;
    int _row;
    int _col;

public:
    Buffer2D();

    Buffer2D(int row, int col);

    int Length();

    int Rows();

    int Cols();

    void* GetAddress();

    void GetBuffer(T *pBuffer, int* row, int* col);

    void CopyBuffer(T *pBuffer, int* row, int* col);

    void CopyBuffer(Rect2N &area, T *pBuffer);

    void CopyBuffer(Vector2N &startVector, Vector2N &endVector, T *pBuffer);

    bool SetBuffer(void* pAddress, int length);

    bool SetBuffer(void* pAddress, int row, int col);

    bool SetBuffer(T* pBuffer, Rect2N &area);

    bool SetBuffer(T* pBuffer, Vector2N &startVector, Vector2N &endVector);

    T Value(int row, int col);

    T Value(Vector2N vector);

    bool SetValue(T value, int row, int col);

    bool SetValue(T value, Vector2N vector);

    bool Equals(IBuffer &buffer);

    void CopyFrom(IBuffer &buffer);

    Buffer2D Clone();
};

typedef Buffer1D<unsigned char> GrayBuffer1D;
typedef Buffer1D<int> ColorBuffer1D;
typedef Buffer2D<unsigned char> GrayBuffer2D;
typedef Buffer2D<int> ColorBuffer2D;

#endif //YOONFACTORY_BUFFER_H