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

    virtual IBuffer Clone() = 0;
};

template <typename T>
struct IBuffer1D<T> : public IBuffer {
    virtual int Length() = 0;

    virtual void* GetAddress() = 0;

    virtual void GetBuffer(T* pBuffer, int* length) = 0;

    virtual void CopyBuffer(T* pBuffer, int* length) = 0;

    virtual void CopyBuffer(int start, int end, T* pBuffer) = 0;

    virtual bool SetBuffer(void* pAddress, int length) = 0;

    virtual bool SetBuffer(T* pBuffer, int start, int end) = 0;

    virtual T Value(int pos) = 0;

    virtual bool SetValue(T value, int pos) = 0;

    virtual bool Equals(IBuffer &buffer) = 0;

    virtual void CopyFrom(IBuffer &buffer) = 0;

    virtual IBuffer Clone() = 0;
};

template <typename T>
struct IBuffer2D<T> : public IBuffer {
    virtual int Length() = 0;

    virtual int Rows() = 0;

    virtual int Cols() = 0;

    virtual void* GetAddress() = 0;

    virtual void GetBuffer(T* pBuffer, int* row, int* col) = 0;

    virtual void CopyBuffer(T* pBuffer, int* row, int* col) = 0;

    virtual void CopyBuffer(Rect2N &area, T* pBuffer) = 0;

    virtual void CopyBuffer(Vector2N &startVector, Vector2N &endVector, T* pBuffer) = 0;

    virtual bool SetBuffer(void* pAddress, int length) = 0;

    virtual bool SetBuffer(void* pAddress, int row, int col) = 0;

    virtual bool SetBuffer(T* pBuffer, Rect2N &area) = 0;

    virtual bool SetBuffer(T* pBuffer, Vector2N &startVector, Vector2N &endVector) = 0;

    virtual T Value(int row, int col);

    virtual T Value(Vector2N vector);

    virtual bool SetValue(T value, int row, int col);

    virtual bool SetValue(T value, Vector2N vector);

    virtual bool Equals(IBuffer &buffer) = 0;

    virtual void CopyFrom(IBuffer &buffer) = 0;

    virtual IBuffer Clone() = 0;
};

class Buffer1D: public IBuffer1D<unsigned char> {
private:
    unsigned char *_pBuffer = null;
    int _length;

public:
    Buffer1D();

    Buffer1D(int length);

    ~Buffer1D();

    int Length();

    void *GetAddress();

    void GetBuffer(unsigned char *pBuffer, int *length);

    void CopyBuffer(unsigned char *pBuffer, int *length);

    void CopyBuffer(int start, int end, unsigned char *pBuffer);

    bool SetBuffer(void *pAddress, int length);

    bool SetBuffer(unsigned char *pBuffer, int start, int end);

    unsigned char Value(int pos);

    bool SetValue(unsigned char value, int pos);

    bool Equals(IBuffer &buffer);

    void CopyFrom(IBuffer &buffer);

    IBuffer Clone();

    bool operator==(const Buffer1D &other);

    bool operator!=(const Buffer1D &other);

    unsigned char &operator[](const int index);
};

class Buffer2D: public IBuffer2D<unsigned char> {
private:
    unsigned char* _pBuffer = null;
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

    void GetBuffer(unsigned char *pBuffer, int* row, int* col);

    void CopyBuffer(unsigned char *pBuffer, int* row, int* col);

    void CopyBuffer(Rect2N &area, unsigned char *pBuffer);

    void CopyBuffer(Vector2N &startVector, Vector2N &endVector, unsigned char *pBuffer);

    bool SetBuffer(void* pAddress, int length);

    bool SetBuffer(void* pAddress, int row, int col);

    bool SetBuffer(unsigned char* pBuffer, Rect2N &area);

    bool SetBuffer(unsigned char* pBuffer, Vector2N &startVector, Vector2N &endVector);

    unsigned char Value(int row, int col);

    unsigned char Value(Vector2N vector);

    bool SetValue(unsigned char value, int row, int col);

    bool SetValue(unsigned char value, Vector2N vector);

    bool Equals(IBuffer &buffer) = 0;

    void CopyFrom(IBuffer &buffer) = 0;

    IBuffer Clone() = 0;
};


class BufferFactory {
public:
    static Buffer1D &Create(void *pAddress, int length) {
        Buffer1D *pBuffer = new Buffer1D();
        pBuffer->SetBuffer(pAddress, length);
        return &pBuffer;
    }

    static Buffer2D &Create(void *pAddress, int row, int col) {
        Buffer2D *pBuffer = new Buffer2D();
        pBuffer->SetBuffer(pAddress, row, col);
        return &pBuffer;
    }
};

#endif //YOONFACTORY_BUFFER_H
