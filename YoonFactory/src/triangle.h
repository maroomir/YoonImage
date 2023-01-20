//
// Created by 윤철중 on 2023/01/20.
//

#ifndef YOONFACTORY_TRIANGLE_H
#define YOONFACTORY_TRIANGLE_H

#include "figure.h"

struct ITriangle : public IFigure {
    virtual ITriangle Clone() = 0;

    virtual void CopyFrom(ITriangle &triangle) = 0;
};

#endif //YOONFACTORY_TRIANGLE_H
