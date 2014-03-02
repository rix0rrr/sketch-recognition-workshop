/**
 * Global configuration settings of our recognition algorithm.
 *
 * You should peruse (and possibly change) the constants here. There may be
 * some magical numbers strewn about the code, but the most important constants
 * are defined in this file.
 */
#ifndef CONFIG_H
#define CONFIG_H

/**
 * PATCHES
 *
 * How many patches to take from each image. We will take patches of SIZExSIZE,
 * offset from each other at STRIDE pixels, both horizontally and vertically.
 *
 * Note: patches will and are allowed to overlap (if STRIDE < SIZE).
 *
 * Hint: wouldn't it be useful if all images had a known size before we went to
 * take patches from them? Think about the Region Of Interest, and aspect
 * ratios.
 */
#define PATCH_SIZE 70
#define PATCH_STRIDE 50

/**
 * FEATURES
 *
 * Into how many bins should we divide the values of our feature space? For
 * example, while binning HSV values, we partition the space of H values,
 * 0..255, into 10 bins of 0..24, 25..49, etc. This will give use generalizing
 * power, and reduce the amount of data we have to work with.
 *
 * The number of features times the number of bins will lead to the length of
 * our feature vector.
 *
 * Hint: a possible improvement comes from soft binning: i.e., instead of
 * increasing the bin count by 1 for every sample, fractionally increase two
 * bins if the value falls somewhere in between.
 */
#define HSV_HISTOGRAM_BINS 10
#define FEATURE_VECTOR_LENGTH (HSV_HISTOGRAM_BINS * 3)

/**
 * TRAINING
 *
 * How much of the total image set should be devoted to training? The remainder
 * is used for the validation set. Between 60%-80% seems to be a generally
 * recommended range.
 */
#define TRAINING_SET_FRACTION 0.7

/**
 * CLUSTERING
 *
 * The size of our vocabulary determines how fine-grained our recognition can
 * be. More is typically better, but leads to MUCH larger running times. This
 * parameter should be tweaked by observing and trying out a couple of
 * different values (i.e., the "wet finger method" :).
 */
#define VISUAL_WORD_COUNT 50

/**
 * CLASSIFICATION
 *
 * These parameters influence the working of the SVM, but their meaning is not
 * easy to intuitively explain. Just as with the vocabulary size, the best
 * values for these should be found experimentally.
 */
#define SVM_GAMMA 0.5
#define SVM_C 5

// This is used for early aborts for debugging/testing
// Set impossibly high for production use :)
#define MAX_IMAGES_PER_CLASS 1000
#define MAX_CLASSES 1000

#endif
