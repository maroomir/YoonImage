//
// Created by maroomir on 22. 12. 31.
//

#ifndef YOONFACTORY_VECTOR_H
#define YOONFACTORY_VECTOR_H

#include "figure.h"

struct IVector : IFigure {
    virtual bool Equals(IVector &vector) = 0;

    virtual IVector Clone() = 0;

    virtual void CopyFrom(IVector &vector) = 0;

    virtual void Zero() = 0;

    virtual IVector Unit() = 0;

    virtual double Length() = 0;

    virtual double Distance(IVector &vector) = 0;
};

#endif //YOONFACTORY_VECTOR_H
