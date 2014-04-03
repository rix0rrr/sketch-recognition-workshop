Compiling on Windows
====================

> (Note: the following has not recently been tested by me, since I don't have a
> Windows machine! If anyone could confirm these instructions and send me pull
> requests for fixes, that would be very much appreciated).

Windows users can use Visual Studio 2010 to compile everything. The solution
contains three projects. One library project that is used by the other two, a
project `trainer` and a project `recognizer`. If you run them from Visual
Studio then everything will work automagically.

If you use the provided Boost and OpenCV libraries, you *must* build the
RELEASE build (because they have been built as Release as well), otherwise the
program won't work properly.

The solution will compile everything to `bin\Release` subdirectory in the root.
If you want to run this from the command-line, then you have to make sure that
your working directory (i.e. the location where you invoke the executables) is
`cpp`, otherwise the trainer cannot find the images it needs.

The projects have two hardcoded dependency directories for Boost and OpenCV.

Boost 
-----

The solution expects Boost to be located in the `boost` subdirectory in the
root of the repository. It should contain another `boost` subdirectory
containing the header files and a `lib32-msvc-10.0` subdirectory containing the
libraries.

This is the layout based on the pre-compiled binaries available at
[http://sourceforge.net/projects/boost/files/boost-binaries/1.54.0/boost_1_54_0-msvc-10.0-32.exe/download](http://sourceforge.net/projects/boost/files/boost-binaries/1.54.0/boost_1_54_0-msvc-10.0-32.exe/download)

OpenCV
------

The solution also expects OpenCV to be located in the `opencv` subdirectory in
the root of the repository. It should contain an `include` subdirectory
containing the header files, a `x86\vc10\bin` subdirectory containing the DLLs
and a `x86\vc10\lib` subdirectory containing the corresponding library files.

This reflects the content of the `build` subdirectory of the pre-compiled
binary package available at
[http://sourceforge.net/projects/opencvlibrary/files/opencv-win/2.4.6/OpenCV-2.4.6.0.exe/download](http://sourceforge.net/projects/opencvlibrary/files/opencv-win/2.4.6/OpenCV-2.4.6.0.exe/download)

