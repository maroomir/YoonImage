//
// Created by 윤철중 on 2023/01/20.
//

#ifndef YOONFACTORY_RECT_H
#define YOONFACTORY_RECT_H

#include "figure.h"
#include "vector.h"

struct IRect : IFigure {
    virtual IRect Clone() = 0;

    virtual void CopyFrom(IRect &rect) = 0;

    virtual bool Equals(IRect &rect) = 0;

    virtual bool IsContain(IVector &vector) = 0;

    virtual float Area() = 0;
};

template <typename T>
struct IRect2D<T> : public IRect {
    virtual IVector2D<T> CenterPos() = 0;

    virtual T Width() = 0;

    virtual T Height() = 0;

    virtual void SetCenterPos(IVector &vector) = 0;

    virtual void SetCenterPos(T x, T y) = 0;

    virtual void SetWidth(T width) = 0;

    virtual void SetHeight(T height) = 0;

    virtual T Left() = 0;

    virtual T Top() = 0;

    virtual T Right() = 0;

    virtual T Bottom() = 0;

    virtual IVector2D<T> TopLeft() = 0;

    virtual IVector2D<T> TopRight() = 0;

    virtual IVector2D<T> BottomLeft() = 0;

    virtual IVector2D<T> BottomRight() = 0;

    virtual void SetVerifiedArea(T minX, T minY, T maxX, T maxY) = 0;

    virtual void SetVerifiedArea(IVector2D<T> &minVector, IVector2D<T> &maxVector) = 0;

    virtual IVector2D<T> Position(eDir2D dir);
};

class Rect2N : public IRect2D<int> {
public:
    const int PropertiesCount() { return 4; }

    void FromArgs(int argc, char *argv[]);

    IFigure Clone();

    IRect Clone();

    void CopyFrom(IRect& rect);

    bool Equals(IRect& rect);

    bool IsContain(IVector& vector);

    float Area();

    Vector2N CenterPos();

    int Width();

    int Height();

    void SetCenterPos(IVector& vector);

    void SetCenterPos(int x, int y);

    void SetWidth(int width);

    void SetHeight(int height);

    int Left();

    int Top();

    int Right();

    int Bottom();

    Vector2N TopLeft();

    Vector2N TopRight();

    Vector2N BottomLeft();

    Vector2N BottomRight();

    void SetVerifiedArea(int minX, int minY, int maxX, int maxY);

    void SetVerifiedArea(Vector2N &minVector, Vector2N &maxVector);

    Vector2N Position(eDir2D dir);
};

class Rect2D : public IRect2D<float> {
public:
    const int PropertiesCount() { return 4; }

    void FromArgs(int argc, char *argv[]);

    IFigure Clone();

    IRect Clone();

    void CopyFrom(IRect& rect);

    bool Equals(IRect& rect);

    bool IsContain(IVector& vector);

    float Area();

    Vector2D CenterPos();

    float Width();

    float Height();

    void SetCenterPos(IVector& vector);

    void SetCenterPos(float x, float y);

    void SetWidth(float width);

    void SetHeight(float height);

    float Left();

    float Top();

    float Right();

    float Bottom();

    Vector2D TopLeft();

    Vector2D TopRight();

    Vector2D BottomLeft();

    Vector2D BottomRight();

    void SetVerifiedArea(float minX, float minY, float maxX, float maxY);

    void SetVerifiedArea(Vector2D &minVector, Vector2D &maxVector);

    Vector2D Position(eDir2D dir);
};

#endif //YOONFACTORY_RECT_H
