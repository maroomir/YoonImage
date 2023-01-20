//
// Created by maroomir on 22. 12. 31.
//

#ifndef YOONFACTORY_FIGURE_H
#define YOONFACTORY_FIGURE_H

struct IFigure {
    virtual const int PropertiesCount() = 0;

    virtual void FromArgs(int argc, char *argv[]) = 0;

    virtual IFigure Clone() = 0;
};

#endif //YOONFACTORY_FIGURE_H
