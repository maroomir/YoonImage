//
// Created by 윤철중 on 2023/01/15.
//

#ifndef YOONFACTORY_MATRIX_H
#define YOONFACTORY_MATRIX_H

#include "vector.h"

struct IMatrix {
    virtual int Length() = 0;

    virtual IMatrix Clone() = 0;

    virtual IMatrix Inverse() = 0;

    virtual IMatrix Transpose() = 0;

    virtual IMatrix Unit() = 0;

    void CopyFrom(IMatrix &matrix);
};

template <typename T>
struct IMatrix<T> : public IMatrix {
    virtual T** Array() = 0;

    virtual void SetArray(T&& array) = 0;

    virtual T Determiant() = 0; // 행렬식

    virtual T Cofactor(int row, int col) = 0; // 여인자

    virtual IMatrix MinorMatrix(int row, int col) = 0; // 소행렬

    virtual IMatrix AdjointMatrix() = 0;  // 수반행렬
};

template <typename T>
struct IMatrix2D<T> : public IMatrix<T> {
    virtual IMatrix SetScaleUnit(T scaleX, T scaleY) = 0;

    virtual IMatrix SetMovementUnit(T moveX, T moveY) = 0;

    virtual IMatrix SetMovementUnit(IVector2D<T>& vector) = 0;

    virtual IMatrix SetRotateUnit(float angle) = 0;
};

template <typename T>
struct IMatrix3D<T> : public IMatrix<T> {
    virtual IMatrix SetScaleUnit(T scaleX, T scaleY, T scaleZ) = 0;

    virtual IMatrix SetMovementUnit(T moveX, T moveY, T moveZ) = 0;

    virtual IMatrix SetMovementUnit(IVector3D<T>& vector) = 0;

    virtual IMatrix SetRotateXUnit(float angle) = 0;

    virtual IMatrix SetRotateYUnit(float angle) = 0;

    virtual IMatrix SetRotateZUnit(float angle) = 0;
};

class Matrix2N : public IMatrix2D<int> {
public:
    int Length();

    IMatrix Clone();

    IMatrix Inverse();

    IMatrix Transpose();

    IMatrix Unit();

    void CopyFrom(IMatrix& matrix);

    int** Array();

    void SetArray(int&& array);

    int Determiant();

    int Cofactor(int row, int col);

    IMatrix MinorMatrix(int row, int col);

    IMatrix AdjointMatrix();

    IMatrix SetScaleUnit(int scaleX, int scaleY);

    IMatrix SetMovementUnit(int moveX, int moveY);

    IMatrix SetMovementUnit(Vector2N vector);

    IMatrix SetRotateUnit(float angle);
};

class Matrix2D : public IMatrix2D<float> {
    int Length();

    IMatrix Clone();

    IMatrix Inverse();

    IMatrix Transpose();

    IMatrix Unit();

    void CopyFrom(IMatrix& matrix);

    float** Array();

    void SetArray(float&& array);

    float Determiant();

    float Cofactor(int row, int col);

    IMatrix MinorMatrix(int row, int col);

    IMatrix AdjointMatrix();

    IMatrix SetScaleUnit(float scaleX, float scaleY);

    IMatrix SetMovementUnit(float moveX, float moveY);

    IMatrix SetMovementUnit(Vector2D vector2D);

    IMatrix SetRotateUnit(float angle);
};

#endif //YOONFACTORY_MATRIX_H
