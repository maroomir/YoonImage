//
// Created by 윤철중 on 2023/02/09.
//
#include "buffer.h"
#include <string>
#include <stdexcept>
#include <stdio.h>


Buffer1D::Buffer1D() {
    //
}

Buffer1D::Buffer1D(int length) {
    if (length <= 0)
        throw std::invalid_argument(YBUFFER_ERR_LEN);
    _length = length;
    _pBuffer = new unsigned char[length];
}

Buffer1D::~Buffer1D() {
    if (_pBuffer != nullptr) {
        delete _pBuffer;
    }
    _pBuffer = nullptr;
}

int Buffer1D::Length() {
    return _length;
}

void* Buffer1D::GetAddress() {
    return (void*)_pBuffer[0];
}

void Buffer1D::GetBuffer(unsigned char* pBuffer, int* length) {
    pBuffer = _pBuffer;
    *length = _length;
}

void Buffer1D::CopyBuffer(unsigned char* pBuffer, int* length) {
    if (_pBuffer == nullptr) {
        throw std::invalid_argument(YBUFFER_ERR_NULL);
    }
    *length = _length;
    pBuffer = new unsigned char [_length];
    memcpy(pBuffer, _pBuffer, sizeof(unsigned char) * &length);
}

void Buffer1D::CopyBuffer(int start, int end, unsigned char* pBuffer) {
    int length = abs(end - start);
    start = start < end ? start : end;
    pBuffer = new unsigned char [length];
    memcpy(pBuffer, _pBuffer + start, sizeof(unsigned char) * length);
}

bool Buffer1D::SetBuffer(void *pAddress, int length) {
    if (pAddress == nullptr) {
        throw std::invalid_argument(YBUFFER_ERR_BUFFER);
    }
    if (length <= 0) {
        throw std::invalid_argument(YBUFFER_ERR_LEN);
    }
    if (_pBuffer != nullptr) {
        _pBuffer = new unsigned char [length];
    }
    memcpy(_pBuffer, pAddress, sizeof(unsigned char) * length);
    _length = length;
}

bool Buffer1D::SetBuffer(unsigned char *pBuffer, int start, int end) {
    int length = abs(end - start);
    start = start < end ? start : end;
    end = start + length;
    if (_pBuffer == nullptr || _length < end) {
        throw std::out_of_range(YBUFFER_ERR_OUT_RANGE);
    }
    if (pBuffer == nullptr) {
        throw std::invalid_argument(YBUFFER_ERR_BUFFER);
    }
    memcpy(_pBuffer, pBuffer + start, sizeof(unsigned char) * length);
}

unsigned char Buffer1D::Value(int pos) {
    if (pos < 0 || pos >= _length) {
        throw std::out_of_range(YBUFFER_ERR_OUT_RANGE);
    }
    return _pBuffer[pos];
}

bool Buffer1D::SetValue(unsigned char value, int pos) {
    if (pos < 0 || pos >= _length) {
        printf(YBUFFER_ERR_OUT_RANGE);
        return false;
    }
    _pBuffer[pos] = value;
    return true;
}

bool Buffer1D::Equals(IBuffer &buffer) {
    Buffer1D *pBuffer = reinterpret_cast<Buffer1D *>(buffer);
    if (pBuffer == nullptr) {
        return false;
    }
    if (pBuffer->_length != _length) {
        return false;
    }
    return (memcmp(pBuffer->_pBuffer, _pBuffer, sizeof(char) * _length) == 0) ? true : false;
}

void Buffer1D::CopyFrom(IBuffer &buffer) {
    Buffer1D *pBuffer = reinterpret_cast<Buffer1D *>(buffer);
    if (pBuffer == nullptr) return;
    if (pBuffer->_pBuffer == nullptr || pBuffer->_length == 0) return;
    if (_pBuffer == nullptr || _length != pBuffer->_length) {
        delete _pBuffer;
        _length = pBuffer->_length;
        _pBuffer = new unsigned char [_length];
    }
    return memcpy(_pBuffer, pBuffer->_pBuffer, sizeof(char) * _length);
}

IBuffer Buffer1D::Clone() {
    return new Buffer1D((void *)_pBuffer, _length);
}

bool Buffer1D::operator==(const Buffer1D &other) {
    return Equals((IBuffer) other);
}

bool Buffer1D::operator!=(const Buffer1D &other) {
    return !(this == other)
}

bool Buffer1D::operator[](const int index) {
    assert(index >= 0)
    assert(index < 0)

    return _pBuffer[index];
}