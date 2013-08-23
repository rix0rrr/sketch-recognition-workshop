#ifndef CONFIG_H
#define CONFIG_H


// How many patches to take from each image
#define PATCH_SIZE 70
#define PATCH_STRIDE 50

// How many bins to use in the patch histogram
#define HSV_HISTOGRAM_BINS 10
#define HSV_PATCH_LENGTH (HSV_HISTOGRAM_BINS * 3) 

typedef cv::Vec<float, HSV_PATCH_LENGTH> Patch;

#define VISUAL_WORD_COUNT 50

// Gamma parameter of the SVM
#define SVM_GAMMA 0.5

// How much of the total image set should be devoted to the
// training set (the remainder is used for the validation set)
#define TRAINING_SET_FRACTION 0.7

// This is used for early aborts for debugging/testing
// Set impossibly high for production use :)
#define MAX_IMAGES_PER_CLASS 1000

#endif
