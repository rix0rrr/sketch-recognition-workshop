Compiling on Mac OS X
=====================

You'll need:

- XCode command line tools (first install XCode, then inside XCode preferences
  install the command-line tools)

- [Homebrew](http://brew.sh/)  if you don't already have it.

- And then use that to install Boost and OpenCV (will take ~15min to compile)

    $ brew install boost homebrew/science/opencv 

After installation, the following should work:

    $ cd cpp/
    $ make
    $ ./trainer
