//
// Created by 윤철중 on 2023/01/20.
//

#ifndef YOONFACTORY_BUFFER_H
#define YOONFACTORY_BUFFER_H

#include "rect.h"
#include "vector.h"

struct IBuffer {
    virtual int Length() = 0;

    virtual void* GetAddress() = 0;

    virtual bool SetBuffer(void* pAddress, int length) = 0;

    virtual bool Equals(IBuffer &buffer) = 0;

    virtual void CopyFrom(IBuffer &buffer) = 0;

    IBuffer Clone() = 0;
};

template <typename T>
struct IBuffer<T> : public IBuffer {
    virtual T* GetBuffer() = 0;

    virtual T* CopyBuffer() = 0;

    virtual bool SetBuffer(T* pBuffer) = 0;
};

template <typename T>
struct IBuffer1D<T> : public IBuffer<T> {
    virtual T* CopyBuffer(int start, int end) = 0;

    virtual bool SetBuffer(T* pBuffer, int start, int end) = 0;

    virtual T Value(int pos) = 0;

    virtual bool SetValue(T value, int pos) = 0;
};

template <typename T>
struct IBuffer2D<T> : public IBuffer<T> {
    virtual int Rows() = 0;

    virtual int Cols() = 0;

    virtual T* CopyBuffer(Rect2N &area) = 0;

    virtual T* CopyBuffer(Vector2N &startVector, Vector2N &endVector) = 0;

    virtual T* SetBuffer(T* pBuffer, Rect2N &area) = 0;

    virtual T* SetBuffer(T* pBuffer, Vector2N &startVector, Vector2N &endVector) = 0;

    virtual T Value(int row, int col);

    virtual T Value(Vector2N vector);

    virtual bool SetValue(T value, int row, int col);

    virtual bool SetValue(T value, Vector2N vector);
};

#endif //YOONFACTORY_BUFFER_H
