//
// Created by maroomir on 22. 12. 31.
//

#ifndef YOONFACTORY_FIGURE_H
#define YOONFACTORY_FIGURE_H

struct IFigure {
    virtual int PropertiesCount() = 0;

    virtual IFigure Clone() = 0;
};

#endif //YOONFACTORY_FIGURE_H
