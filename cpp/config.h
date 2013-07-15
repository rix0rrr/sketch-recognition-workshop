#ifndef CONFIG_H
#define CONFIG_H


// How many patches to take from each image
#define PATCH_SIZE 70
#define PATCH_STRIDE 50

// How many bins to use in the patch histogram
#define HSV_HISTOGRAM_BINS 10
#define HSV_PATCH_LENGTH (HSV_HISTOGRAM_BINS * 3) 

typedef cv::Vec<float, HSV_PATCH_LENGTH> Patch;

#define VISUAL_WORD_COUNT 10

#endif
