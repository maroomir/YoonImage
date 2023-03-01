//
// Created by 윤철중 on 2023/02/09.
//
#include "buffer.h"
#include <string>
#include <stdexcept>
#include <cstdio>

template <typename T>
Buffer1D<T>::Buffer1D(int length) {
    if (length <= 0)
        throw std::invalid_argument(YBUFFER_ERR_LEN);
    _length = length;
    _pBuffer = new T[length];
}

template <typename T>
Buffer1D<T>::~Buffer1D() {
    delete _pBuffer;
    _pBuffer = nullptr;
}

template <typename T>
int Buffer1D<T>::Length() {
    return _length;
}

template <typename T>
void* Buffer1D<T>::GetAddress() {
    if (_pBuffer == nullptr) return nullptr;
    return (void*)_pBuffer[0];
}

template <typename T>
void Buffer1D<T>::GetBuffer(T* pBuffer, int* length) {
    if (_pBuffer == nullptr) return;
    pBuffer = _pBuffer;
    *length = _length;
}

template <typename T>
void Buffer1D<T>::CopyBuffer(T* pBuffer, int* length) {
    if (_pBuffer == nullptr) {
        throw std::invalid_argument(YBUFFER_ERR_NULL);
    }
    *length = _length;
    pBuffer = new T [_length];
    memcpy(pBuffer, _pBuffer, sizeof(T) * _length);
}

template <typename T>
void Buffer1D<T>::CopyBuffer(int start, int end, T* pBuffer) {
    int length = abs(end - start);
    start = start < end ? start : end;
    pBuffer = new T [length];
    memcpy(pBuffer, _pBuffer + start, sizeof(T) * length);
}

template <typename T>
bool Buffer1D<T>::SetBuffer(void *pAddress, int length) {
    if (pAddress == nullptr) {
        throw std::invalid_argument(YBUFFER_ERR_BUFFER);
    }
    if (length <= 0) {
        throw std::invalid_argument(YBUFFER_ERR_LEN);
    }
    if (_pBuffer != nullptr) {
        _pBuffer = new T [length];
    }
    memcpy(_pBuffer, pAddress, sizeof(T) * length);
    _length = length;
}

template <typename T>
bool Buffer1D<T>::SetBuffer(T *pBuffer, int start, int end) {
    int length = abs(end - start);
    start = start < end ? start : end;
    end = start + length;
    if (_pBuffer == nullptr || _length < end) {
        throw std::out_of_range(YBUFFER_ERR_OUT_RANGE);
    }
    if (pBuffer == nullptr) {
        throw std::invalid_argument(YBUFFER_ERR_BUFFER);
    }
    memcpy(_pBuffer, pBuffer + start, sizeof(T) * length);
}

template <typename T>
T Buffer1D<T>::Value(int pos) {
    if (pos < 0 || pos >= _length) {
        throw std::out_of_range(YBUFFER_ERR_OUT_RANGE);
    }
    return _pBuffer[pos];
}

template <typename T>
bool Buffer1D<T>::SetValue(T value, int pos) {
    if (pos < 0 || pos >= _length) {
        printf(YBUFFER_ERR_OUT_RANGE);
        return false;
    }
    _pBuffer[pos] = value;
    return true;
}

template <typename T>
bool Buffer1D<T>::Equals(IBuffer &buffer) {
    auto *pBuffer = reinterpret_cast<Buffer1D *>(buffer);
    if (pBuffer == nullptr) {
        return false;
    }
    if (pBuffer->_length != _length) {
        return false;
    }
    return (memcmp(pBuffer->_pBuffer, _pBuffer, sizeof(char) * _length) == 0);
}

template <typename T>
void Buffer1D<T>::CopyFrom(IBuffer &buffer) {
    auto *pBuffer = reinterpret_cast<Buffer1D *>(buffer);
    if (pBuffer == nullptr) return;
    if (pBuffer->_pBuffer == nullptr || pBuffer->_length == 0) return;
    if (_pBuffer == nullptr || _length != pBuffer->_length) {
        delete _pBuffer;
        _length = pBuffer->_length;
        _pBuffer = new T [_length];
    }
    return memcpy(_pBuffer, pBuffer->_pBuffer, sizeof(char) * _length);
}

template <typename T>
Buffer1D<T> Buffer1D<T>::Clone() {
    return new Buffer1D((void *)_pBuffer, _length);
}

template <typename T>
bool Buffer1D<T>::operator==(const Buffer1D &other) {
    return Equals((IBuffer) other);
}

template <typename T>
bool Buffer1D<T>::operator!=(const Buffer1D &other) {
    return this != other;
}

template <typename T>
T & Buffer1D<T>::operator[] (int index) {
    assert(index >= 0);
    assert(index < 0);

    return _pBuffer[index];
}