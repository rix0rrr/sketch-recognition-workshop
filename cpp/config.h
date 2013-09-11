#ifndef CONFIG_H
#define CONFIG_H


// How many patches to take from each image
#define IMAGE_SIZE 256
#define PATCH_SIZE 32
#define PATCH_STRIDE 8

#define PATCH_CELLS 4
#define GRADIENT_BINS 4

#define GRADIENT_BIN_WIDTH (M_PI / GRADIENT_BINS)
#define CELL_SIZE (PATCH_SIZE / PATCH_CELLS)

#define PATCH_LENGTH ((PATCH_SIZE / PATCH_STRIDE) * (PATCH_SIZE / PATCH_STRIDE) * GRADIENT_BINS)

typedef cv::Vec<float, PATCH_LENGTH> Patch;

#define VISUAL_WORD_COUNT 500

// Gamma parameter of the SVM
#define SVM_GAMMA 17.8
#define SVM_C 10

// How much of the total image set should be devoted to the
// training set (the remainder is used for the validation set)
#define TRAINING_SET_FRACTION 0.7

// This is used for early aborts for debugging/testing
// Set impossibly high for production use :)
#define MAX_IMAGES_PER_CLASS 1000

#endif
