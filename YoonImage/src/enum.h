//
// Created by maroomir on 2021-07-05.
//

#ifndef YOONIMAGE_ENUM_H
#define YOONIMAGE_ENUM_H

#define INVALID_INTEGER -65536
#define INVALID_DOUBLE -65536.00

typedef enum {
    DIR_NONE = -1,
    DIR_CENTER,
    DIR_TOP_LEFT,
    DIR_TOP,
    DIR_TOP_RIGHT,
    DIR_RIGHT,
    DIR_BOTTOM_RIGHT,
    DIR_BOTTOM,
    DIR_BOTTOM_LEFT,
    DIR_LEFT,
} eDir2D;

typedef enum {
    FORMAT_NONE = -1,
    FORMAT_GRAY,
    FORMAT_RGB,
    FORMAT_RGB_PARALLEL,
    FORMAT_RGB_MIXED,
    FORMAT_BGR,
    FORMAT_BGR_PARALLEL,
    FORMAT_BGR_MIXED,
} eImageFormat;

#endif //YOONIMAGE_ENUM_H
