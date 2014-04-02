Compiling on Linux (Ubuntu)
===========================

- Make sure the following dependencies are installed:

    libcv-dev
    libopencv-contrib-dev
    libhighgui-dev
    libboost-all-dev

- Go to the `cpp` subdirectory and run

    $ make
    $ ./trainer

The trainer will start to build a datafile of the images in `../images`
 
- Classify new images with:

    $ ./recognizer <path to image>
