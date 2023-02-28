//
// Created by 윤철중 on 2023/01/20.
//

#ifndef YOONFACTORY_LINE_H
#define YOONFACTORY_LINE_H

#include "figure.h"
#include "vector.h"
#include "rect.h"

#define _YOONLINE_INVALID_NUM = -65536;

struct ILine : public IFigure {
    virtual float Length() = 0;

    virtual float Slope() = 0;

    virtual float Constant() = 0;

    virtual ILine Clone() = 0;

    virtual void CopyFrom(ILine &line) = 0;

    virtual bool Equals(ILine &line) = 0;

    virtual bool IsContain(IVector &vector) = 0;

    virtual float Distance(IVector &vector) = 0;
};

template <typename T>
struct ILine2D<T> : public ILine {
    virtual IVector2D<T> StartPos() = 0;

    virtual IVector2D<T> EndPos() = 0;

    virtual IVector2D<T> CenterPos() = 0;

    virtual IRect2D<T> Area() = 0;

    virtual T X(T y) = 0;

    virtual T Y(T x) = 0;

    virtual IVector2D<T> Intersection(ILine &line) = 0;

    virtual void Fit(IRect2D<T> &rect) = 0;

    virtual void Fit(T width, T height) = 0;

    virtual ILine FlipX(T x) = 0;

    virtual ILine FlipY(T y) = 0;
};

public class Line2N : ILine2D<int> {
private:
    Vector2N _startPos = new Vector2N();
    Vector2N _endPos = new Vector2N();
    float _slope;
    float constant;

public:
    float Length();

    float Slope();

    float Constant();

    ILine Clone();

    void CopyFrom(ILine &line);

    bool Equals(ILine &line);

    bool IsContain(IVector &vector);

    float Distance(IVector &vector);

    IVector2D<int> StartPos();

    IVector2D<int> EndPos();

    IVector2D<int> CenterPos();

    IRect2D<int> Area();

    int X(int y);

    int Y(int x);

    IVector2D<int> Intersection(ILine &line);

    void Fit(IRect2D<int> &rect);

    void Fit(int width, int height);

    ILine FlipX(int x);

    ILine FlipY(int y);
};

public class Line2D : ILine2D<float> {
private:
    Vector2D _startPos = new Vector2D();
    Vector2D _endPos = new Vector2D();
    float _slope;
    float constant;

public:
    float Length();

    float Slope();

    float Constant();

    ILine Clone();

    void CopyFrom(ILine &line);

    bool Equals(ILine &line);

    bool IsContain(IVector &vector);

    float Distance(IVector &vector);

    IVector2D<float> StartPos();

    IVector2D<float> EndPos();

    IVector2D<float> CenterPos();

    IRect2D<float> Area();

    float X(float y);

    float Y(float x);

    IVector2D<float> Intersection(ILine &line);

    void Fit(IRect2D<float> &rect);

    void Fit(float width, float height);

    ILine FlipX(float x);

    ILine FlipY(float y);
};

#endif //YOONFACTORY_LINE_H
