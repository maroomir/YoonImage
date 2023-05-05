#ifndef YOONIMAGE_FIGURE_H_
#define YOONIMAGE_FIGURE_H_

namespace yoonfactory {
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
    } DIR_2D;

    template<typename T>
    struct point2d {
        T x;
        T y;
    };

    template<typename T>
    struct point3d {
        T x;
        T y;
        T z;
    };

    typedef point2d<int> point2d_i;
    typedef point2d<float> point2d_f;
    typedef point3d<int> point3d_i;
    typedef point3d<float> point3d_f;
}

#endif // YOONIMAGE_FIGURE_H_
