//
// Created by 윤철중 on 2023/03/01.
//
#include "buffer.h"
#include <string>
#include <stdexcept>
#include <cmath>

template<typename T>
Buffer2D<T>::Buffer2D(int row, int col) {
    if (row <= 0 || col <= 0)
        throw std::invalid_argument(YBUFFER_ERR_LEN);
    _length = row * col;
    _row = row;
    _col = col;
    _pBuffer = new T[_length];
}

template<typename T>
Buffer2D<T>::~Buffer2D() {
    delete _pBuffer;
    _pBuffer = nullptr;
}

template<typename T>
int Buffer2D<T>::Length() {
    return _length;
}

template<typename T>
int Buffer2D<T>::Rows() {
    return _row;
}

template<typename T>
int Buffer2D<T>::Cols() {
    return _col;
}

template<typename T>
void* Buffer2D<T>::GetAddress() {
    return (void *)_pBuffer;
}

template<typename T>
void Buffer2D<T>::GetBuffer(T *pBuffer, int *row, int *col) {
    if (_pBuffer == nullptr) return;
    pBuffer = _pBuffer;
    *row = _row;
    *col = _col;
}

template<typename T>
void Buffer2D<T>::CopyBuffer(T *pBuffer, int *row, int *col) {
    if (_pBuffer == nullptr) {
        throw std::invalid_argument(YBUFFER_ERR_NULL);
    }
    *row = _row;
    *col = _col;
    pBuffer = new T [_length];
    memcpy(pBuffer, _pBuffer, sizeof(T) * _length);
}

template<typename T>
void Buffer2D<T>::CopyBuffer(Rect2N &area, T *pBuffer) {
    if (_pBuffer == nullptr || _length == 0) {
        throw std::invalid_argument(YBUFFER_ERR_NULL);
    }
    if (area.Width() <= 0 || area.Height() <= 0 || area.Left() <= 0 || area.Top() <= 0) {
        throw std::out_of_range(YBUFFER_ERR_OUT_RANGE);
    }
    if (area.Right() > _col || area.Bottom() > _row) {
        throw std::out_of_range(YBUFFER_ERR_OUT_RANGE);
    }
    int length = area.Width() * area.Height();
    pBuffer = new T[length];
    for (int y = 0; y < area.Height(); y++) {
        int curY = area.Top() + y;
        memcpy(pBuffer + y * area.Width(), _pBuffer + curY * area.Width() + area.Left(), sizeof(T) * area.Width());
    }
}

template<typename T>
void Buffer2D<T>::CopyBuffer(Vector2N &startVector, Vector2N &endVector, T *pBuffer) {
    //
}

template<typename T>
bool Buffer2D<T>::SetBuffer(void *pAddress, int length) {
    if (length <= 0) {
        printf(YBUFFER_ERR_LEN);
        return false;
    }
    int size = (int) std::sqrt(length);
    _row = size;
    _col = size;
    _length = size * size;
    if (_pBuffer != nullptr) {
        _pBuffer = new T[_length];
    }
    memcpy(_pBuffer, pAddress, sizeof(T) * _length);
    return true;
}

template<typename T>
bool Buffer2D<T>::SetBuffer(void *pAddress, int row, int col) {
    if (row <= 0 || col <= 0) {
        printf(YBUFFER_ERR_LEN);
        return false;
    }
    _row = row;
    _col = col;
    _length = row * col;
    if (_pBuffer != nullptr) {
        _pBuffer = new T[_length];
    }
    memcpy(_pBuffer, pAddress, sizeof(T) * _length);
    return true;
}

template<typename T>
bool Buffer2D<T>::SetBuffer(T *pBuffer, Rect2N &area) {
    if (_pBuffer == nullptr || _length == 0) {
        throw std::invalid_argument(YBUFFER_ERR_NULL);
    }
    if (area.Width() <= 0 || area.Height() <= 0 || area.Left() <= 0 || area.Top() <= 0) {
        throw std::out_of_range(YBUFFER_ERR_OUT_RANGE);
    }
    if (area.Right() > _col || area.Bottom() > _row) {
        throw std::out_of_range(YBUFFER_ERR_OUT_RANGE);
    }
    for (int y=0; y < area.Height(); y++) {
        int curY = area.Top() + y;
        memcpy(_pBuffer + curY * area.Width() + area.Left(), pBuffer + y * area.Width(), sizeof(T) * area.Width());
    }
}

template<typename T>
bool Buffer2D<T>::SetBuffer(T *pBuffer, Vector2N &startVector, Vector2N &endVector) {
    //
}

template<typename T>
T Buffer2D<T>::Value(int row, int col) {
    //
}

template<typename T>
T Buffer2D<T>::Value(const Vector2N& vector) {
    //
}

template<typename T>
bool Buffer2D<T>::SetValue(T value, int row, int col) {
    //
}

template<typename T>
bool Buffer2D<T>::SetValue(T value, const Vector2N& vector) {
    //
}

template<typename T>
bool Buffer2D<T>::Equals(buffer_base &buffer) {
    //
}

template<typename T>
void Buffer2D<T>::CopyFrom(buffer_base &buffer) {
    //
}

template<typename T>
Buffer2D<T> Buffer2D<T>::Clone() {
    //
}

template<typename T>
bool Buffer2D<T>::operator==(const Buffer2D<T> &other) {
    //
}

template<typename T>
bool Buffer2D<T>::operator!=(const Buffer2D<T> &other) {
    //
}

template<typename T>
Buffer1D<T> & Buffer2D<T>::operator[](int index) {
    //
}