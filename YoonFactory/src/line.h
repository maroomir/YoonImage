//
// Created by 윤철중 on 2023/01/20.
//

#ifndef YOONFACTORY_LINE_H
#define YOONFACTORY_LINE_H

#include "figure.h"
#include "vector.h"
#include "rect.h"

struct ILine : public IFigure {
    virtual float Length() = 0;

    virtual float Slope() = 0;

    virtual float Constant() = 0;

    virtual ILine Clone() = 0;

    virtual CopyFrom(ILine &line) = 0;

    virtual Equals(ILine &line) = 0;

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

    virtual void Fit(IYoonRect2D<T> &rect) = 0;

    virtual void Fit(T width, T height) = 0;

    virtual ILine FlipX(T x) = 0;

    virtual ILine FlipY(T y) = 0;
};

#endif //YOONFACTORY_LINE_H
