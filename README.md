# SWOC framework #

The SWOC framework is a set of two executables that implement a machine learning algorithm for classifying images of flowers. It serves as a basis for classifying hand-drawn images.

## What is it? ##

### Trainer ###

This is the first step in the process. This executable will index all the image files in the `images` subfolder and divide it randomly into two subsets. One subset is used to train the machine learning algorithm. The other subset for validating what is learned. This executable will store everything it learned in two files, `learned-vocabulary.dat` and `learned-svm.dat`, which serve as input to the second executable.

### Recognizer ###

This executable uses the output of the training step to recognize the class of the images it is given. It accepts one or more images and shows for each image what class it "thinks" it belongs to. 

## How to compile ##

All sources are located in the `cpp` subdirectory. All the images used for training are located in the `images` subdirectory.

The application uses [Boost](http://www.boost.org/) and [OpenCV 2](http://opencv.org/).

### Linux (Ubuntu) ###

- Make sure the following dependencies are installed:

		libcv-dev
		libopencv-contrib-dev
		libhighgui-dev
		libboost-dev

- Go to the `cpp` subdirectory and run

		make
		./trainer

	Now the trainer will start to build a datafile of the images in `../images`
 
- Classify new images with:

		./recognizer <path to image>


### Windows ###

Windows users can use Visual Studio 2010 to compile everything. The solution contains three projects. One library project that is used by the other two, a project `trainer` and a project `recognizer`. If you run them from Visual Studio then everything will work automagically.

The solution will compile everything to a `bin\Debug` or `bin\Release` subdirectory in the root. If you want to run this from the command-line, then you have to make sure that your working directory (i.e. the location where you invoke the executables) is `cpp`, otherwise the trainer cannot find the images it needs.

The projects have two hardcoded dependency directories for Boost and OpenCV.

#### Boost ####

The solution expects Boost to be located in the `boost` subdirectory in the root of the repository. It should contain another `boost` subdirectory containing the header files and a `lib32-msvc-10.0` subdirectory containing the libraries.

This is the layout based on the pre-compiled binaries available at [http://sourceforge.net/projects/boost/files/boost-binaries/1.54.0/boost_1_54_0-msvc-10.0-32.exe/download](http://sourceforge.net/projects/boost/files/boost-binaries/1.54.0/boost_1_54_0-msvc-10.0-32.exe/download)

#### OpenCV ####

The solution also expects OpenCV to be located in the `opencv` subdirectory in the root of the repository. It should contain an `include` subdirectory containing the header files, a `x86\vc10\bin` subdirectory containing the DLLs and a `x86\vc10\lib` subdirectory containing the corresponding library files.

This reflects the content of the `build` subdirectory of the pre-compiled binary package available at [http://sourceforge.net/projects/opencvlibrary/files/opencv-win/2.4.6/OpenCV-2.4.6.0.exe/download](http://sourceforge.net/projects/opencvlibrary/files/opencv-win/2.4.6/OpenCV-2.4.6.0.exe/download)

#### Isn't there a simpler solution? ####

Yes, there is. We've assembled all the necessities in one downloadable zip file that you can just extract to the root folder of this project. You can download it from [https://www.dropbox.com/s/ejbi7thaoccat6d/swoc-framework-libs-msvc10.zip](https://www.dropbox.com/s/ejbi7thaoccat6d/swoc-framework-libs-msvc10.zip)


## What's next? ##

Uhm well, just rewrite all the necessary parts so the two executables accept black and white images of hand-drawn object.

A few tips:

- The current implementation is meant for classifying colored images of flowers (see `Image` class). It divides each image in a number of patches and for each patch it creates an [HSV](http://en.wikipedia.org/wiki/HSL_and_HSV) histogram. This is used as input for the machine learning step. HSV... not gonna work for black and white images.
- Use the following zip file as a training dataset [http://cybertron.cg.tu-berlin.de/eitz/projects/classifysketch/sketches_png.zip](http://cybertron.cg.tu-berlin.de/eitz/projects/classifysketch/sketches_png.zip). We will use that as well.

Good luck, have fun ;)
