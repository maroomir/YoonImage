//
// Created by maroomir on 22. 12. 31.
//

#ifndef YOONFACTORY_BUFFER_H
#define YOONFACTORY_BUFFER_H

struct IBuffer {
    virtual int Length() = 0;
    virtual void* Address() = 0;
    bool Set(void* pAddress, int nLength) = 0;
    bool Equals(IBuffer buffer);
    void CopyFrom(IBuffer buffer);
    IBuffer Clone();
};

template <typename T>
struct IBuffer<T> : IBuffer {
    T* Buffer();
    T* CopyBuffer();
    bool Set(T* pBuffer);
};

template <typename T>
sturct IBuffer1D<T> : IBuffer {
    T* CopyBuffer(int nStart, int nEnd);
    bool SetBuffer(T* pBuffer, int nStart, int nEnd);
    T Get(int nPos);
    bool Set(T value, int nPos);
};

#endif //YOONFACTORY_BUFFER_H
