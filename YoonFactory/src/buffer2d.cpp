//
// Created by 윤철중 on 2023/02/10.
//
#include "buffer.h"

Buffer2D::Buffer2D() {
    //
}

Buffer2D::Buffer2D(int row, int col) {
    //
}

int Buffer2D::Length() {
    //
}

int Buffer2D::Rows() {
    //
}

int Buffer2D::Cols() {
    //
}

void* Buffer2D::GetAddress() {
    //
}

void Buffer2D::GetBuffer(unsigned char *pBuffer, int* row, int* col) {
    //
}

void Buffer2D::CopyBuffer(unsigned char *pBuffer, int* row, int* col) {
    //
}

void Buffer2D::CopyBuffer(Rect2N &area, unsigned char *pBuffer) {
    //
}

void Buffer2D::CopyBuffer(Vector2N &startVector, Vector2N &endVector, unsigned char *pBuffer) {
    //
}

bool Buffer2D::SetBuffer(void *pAddress, int length) {
    //
}

bool Buffer2D::SetBuffer(unsigned char *pBuffer, Rect2N &area) {
    //
}

bool Buffer2D::SetBuffer(unsigned char *pBuffer, Vector2N &startVector, Vector2N &endVector) {
    //
}

bool Buffer2D::SetBuffer(unsigned char *pBuffer) {
    //
}

bool Buffer2D::SetBuffer(void *pAddress, int length) {
    //
}

unsigned char Buffer2D::Value(int row, int col) {
    //
}

unsigned char Buffer2D::Value(Vector2N vector) {
    //
}

bool Buffer2D::SetValue(unsigned char value, int row, int col) {
    //
}

bool Buffer2D::SetValue(unsigned char value, Vector2N vector) {
    //
}