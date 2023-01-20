//
// Created by maroomir on 22. 12. 31.
//

#ifndef YOONFACTORY_VECTOR_H
#define YOONFACTORY_VECTOR_H

#include "enums.h"
#include "figure.h"

struct IVector : public IFigure {
    virtual bool Equals(IVector &vector) = 0;

    virtual IVector Clone() = 0;

    virtual void CopyFrom(IVector &vector) = 0;

    virtual void Zero() = 0;

    virtual IVector Unit() = 0;

    virtual float Length() = 0;

    virtual float Distance(IVector &vector) = 0;
};

template <typename T>
struct IVector2D : public IVector {
    virtual T W() = 0;

    virtual T X() = 0;

    virtual T Y() = 0;

    virtual T* Array() = 0;

    virtual void SetX(T x) = 0;

    virtual void SetY(T y) = 0;

    virtual void SetXY(T x, T y) = 0;

    virtual void SetXY(T &xy) = 0;

    virtual float Angle2D(IVector &vector) = 0;

    virtual eDir2D Direction() = 0;

    virtual void SetDirection(eDir2D dir) = 0;

    virtual eDir2D DirectionTo(IVector &vector) = 0;

    virtual void SetMinValue(T minX, T minY) = 0;

    virtual void SetMaxValue(T maxX, T maxY) = 0;

    virtual void SetMinMaxValue(T minX, T minY, T maxX, T maxY) = 0;

    virtual bool VerifyMinMax(T minX, T minY, T maxX, T maxY) = 0;

    virtual IVector GetScaleVector(T scaleX, T scaleY) = 0;

    virtual IVector GetNextVector(T moveX, T moveY) = 0;

    virtual IVector GetNextVector(IVector &vector) = 0;

    virtual IVector GetNextVector(eDir2D dir) = 0;

    virtual IVector GetRotateVector(float angle) = 0;

    virtual IVector GetRotateVector(IVector &center, float angle) = 0;

    virtual void Scale(T scaleX, T scaleY) = 0;

    virtual void Move(T moveX, T moveY) = 0;

    virtual void Move(IVector &vector) = 0;

    virtual void Move(eDir2D dir) = 0;

    virtual void Rotate(float angle) = 0;

    virtual void Rotate(IVector &center, float angle) = 0;
};

template <typename T>
struct IVector3D : public IVector {
    virtual T W() = 0;

    virtual T X() = 0;

    virtual T Y() = 0;

    virtual T Z() = 0;

    virtual T* Array() = 0;

    virtual void SetX(T x) = 0;

    virtual void SetY(T y) = 0;

    virtual void SetZ(T z) = 0;

    virtual void SetXYZ(T x, T y, T z) = 0;

    virtual void SetXYZ(T &xyz) = 0;

    virtual float AngleX(IVector &vector) = 0;

    virtual float AngleY(IVector &vector) = 0;

    virtual float AngleZ(IVector &vector) = 0;

    virtual IVector GetScaleVector(T scaleX, T scaleY, T scaleZ) = 0;

    virtual IVector GetNextVector(T moveX, T moveY, T moveZ) = 0;

    virtual IVector GetNextVector(IVector &vector) = 0;

    virtual void Scale(T scaleX, T scaleY, T scaleZ) = 0;

    virtual void Move(T x, T y, T z) = 0;

    virtual void Move(IVector &vector) = 0;

    virtual void RotateX(float angle) = 0;

    virtual void RotateY(float angle) = 0;

    virtual void RotateZ(float angle) = 0;
};

class Vector2N : public IVector2D<int> {
public:
    const int PropertiesCount() { return 2; }

    void FromArgs(int argc, char *argv[]);

    IFigure Clone();

    IVector Clone();

    void CopyFrom(IVector &vector);

    void Zero();

    IVector Unit();

    float Length();

    float Distance(IVector &vector);

    int W();

    int X();

    int Y();

    int* Array();

    void SetX(int x);

    void SetY(int Y);

    void SetXY(int x, int y);

    void SetXY(int& xy);

    float Angle2D(IVector &vector);

    eDir2D Direction();

    void SetDirection(eDir2D dir);

    eDir2D DirectionTo(IVector &vector);

    void SetMinValue(int minX, int minY);

    void SetMaxValue(int maxX, int maxY);

    void SetMinMaxValue(int minX, int minY, int maxX, int maxY);

    bool VerifyMinMax(int minX, int minY, int maxX, int maxY);

    IVector GetScaleVector(int scaleX, int scaleY);

    IVector GetNextVector(int moveX, int moveY);

    IVector GetNextVector(IVector& vector);

    IVector GetNextVector(eDir2D dir);

    IVector GetRotateVector(float angle);

    IVector GetRotateVector(IVector& center, float angle);

    void Scale(int scaleX, int scaleY);

    void Move(int moveX, int moveY);

    void Move(IVector& vector);

    void Move(eDir2D dir);

    void Rotate(float angle);

    void Rotate(IVector& center, float angle);
};

class Vector2D : public IVector2D<float> {
public:
    const int PropertiesCount() { return 2; }

    void FromArgs(int argc, char *argv[]);

    IFigure Clone();

    IVector Clone();

    void CopyFrom(IVector &vector);

    void Zero();

    IVector Unit();

    float Length();

    float Distance(IVector &vector);

    float W();

    float X();

    float Y();

    float* Array();

    void SetX(float x);

    void SetY(float y);

    void SetXY(float x, float y);

    void SetXY(float& xy);

    float Angle2D(IVector &vector);

    eDir2D Direction();

    void SetDirection(eDir2D dir);

    eDir2D DirectionTo(IVector &vector);

    void SetMinValue(float minX, float minY);

    void SetMaxValue(float maxX, float maxY);

    void SetMinMaxValue(float minX, float minY, float maxX, float maxY);

    bool VerifyMinMax(float minX, float minY, float maxX, float maxY);

    IVector GetScaleVector(float scaleX, float scaleY);

    IVector GetNextVector(float moveX, float moveY);

    IVector GetNextVector(IVector& vector);

    IVector GetNextVector(eDir2D dir);

    IVector GetRotateVector(float angle);

    IVector GetRotateVector(IVector& center, float angle);

    void Scale(float scaleX, float scaleY);

    void Move(float moveX, float moveY);

    void Move(IVector& vector);

    void Move(eDir2D dir);

    void Rotate(float angle);

    void Rotate(IVector& center, float angle);

};

#endif //YOONFACTORY_VECTOR_H
