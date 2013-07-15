#CXX=g++

SRCS    := recognizer.cpp ImageRepository.cpp rgb_to_hsv.cpp ImageClass.cpp Image.cpp
OBJS    := ${SRCS:.cpp=.o} 
DEPS    := ${SRCS:.cpp=.dep} 
XDEPS   := $(wildcard ${DEPS}) 

TARGET  := recognizer

ifeq (${WIN},yes)
TARGET  := bothead-win/bothead
LIBS     = -lopencv_core 
CXXFLAGS = -O2 -Wall -I../../shared -I../lib/curses  -I../lib/pthread/include -I../lib/d2xx/lib-win
LDFLAGS  = -L../lib/pthread/lib ${XLDFLAGS}
else
# Otherwise, lib should be installed into /usr/lib
LIBS     = -lopencv_core -lopencv_highgui -lboost_filesystem-mt -lboost_system-mt
CXXFLAGS = -O2 -Wall
LDFLAGS  = ${XLDFLAGS}
endif

.PHONY: all clean distclean test
all:: ${TARGET} 

ifneq (${XDEPS},) 
include ${XDEPS} 
endif 

${TARGET}: ${OBJS} 
	${CXX} ${LDFLAGS} -o $@ $^ ${LIBS} 

${OBJS}: %.o: %.cpp %.dep 
	${CXX} ${CXXFLAGS} -o $@ -c $< 

${DEPS}: %.dep: %.cpp Makefile 
	${CXX} ${CXXFLAGS} -MM $< > $@ 

clean:
	rm -rf *~ *.o *.dep ${TARGET}

distclean:: clean
