#ifndef RGB_TO_HSV_INT_H
#define RGB_TO_HSV_INT_H

typedef struct rgb_color {
    double r, g, b;    /* Channel intensities between 0 and 255 */
} rgb_color_t;

typedef struct hsv_color {
    double hue;        /* Hue degree between 0 and 255 */
    double sat;        /* Saturation between 0 (gray) and 255 */
    double val;        /* Value between 0 (black) and 255 */
} hsv_color_t;

struct hsv_color rgb_to_hsv(struct rgb_color rgb);

#endif
