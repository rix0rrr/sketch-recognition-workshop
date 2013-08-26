#CXX=g++

TRAINER_SRCS := trainer.cpp ImageRepository.cpp rgb_to_hsv.cpp ImageClass.cpp Image.cpp util.cpp ClassLabelsFile.cpp hogdescriptor_visu.cpp
TRAINER_OBJS := ${TRAINER_SRCS:.cpp=.o} 
TRAINER_DEPS := ${TRAINER_SRCS:.cpp=.dep} 

RECOGNIZER_SRCS := recognizer.cpp Image.cpp rgb_to_hsv.cpp ClassLabelsFile.cpp hogdescriptor_visu.cpp
RECOGNIZER_OBJS := ${RECOGNIZER_SRCS:.cpp=.o} 
RECOGNIZER_DEPS := ${RECOGNIZER_SRCS:.cpp=.dep} 

TESTER_SRCS := tester.cpp ImageRepository.cpp rgb_to_hsv.cpp ImageClass.cpp Image.cpp util.cpp ClassLabelsFile.cpp hogdescriptor_visu.cpp
TESTER_OBJS := ${TESTER_SRCS:.cpp=.o} 
TESTER_DEPS := ${TESTER_SRCS:.cpp=.dep} 

OBJS    := $(sort ${TRAINER_OBJS} ${RECOGNIZER_OBJS} ${TESTER_OBJS})
DEPS    := $(sort ${TRAINER_DEPS} ${RECOGNIZER_DEPS} ${TESTER_DEPS})
XDEPS   := $(wildcard ${TRAINER_DEPS}) $(wildcard ${RECOGNIZER_DEPS}) $(wildcard ${TESTER_DEPS}) 

TRAINER_TARGET    := trainer
RECOGNIZER_TARGET := recognizer
TESTER_TARGET     := tester
TARGETS           := ${TRAINER_TARGET} ${RECOGNIZER_TARGET} ${TESTER_TARGET}

ifeq (${WIN},yes)
#TARGET  := bothead-win/bothead
#LIBS     = -lopencv_core -lopencv_ml -lopencv_imgproc
#CXXFLAGS = -O2 -Wall -I../../shared -I../lib/curses  -I../lib/pthread/include -I../lib/d2xx/lib-win
#LDFLAGS  = -L../lib/pthread/lib ${XLDFLAGS}
else
# Otherwise, lib should be installed into /usr/lib
LIBS     = -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_ml -lboost_filesystem-mt -lboost_system-mt
CXXFLAGS = -O2 -Wall
LDFLAGS  = ${XLDFLAGS}
endif

.PHONY: all clean distclean test
all:: ${TARGETS} 

ifneq (${XDEPS},) 
include ${XDEPS} 
endif 

${TRAINER_TARGET}: ${TRAINER_OBJS} 
	${CXX} ${LDFLAGS} -o $@ $^ ${LIBS} 

${RECOGNIZER_TARGET}: ${RECOGNIZER_OBJS} 
	${CXX} ${LDFLAGS} -o $@ $^ ${LIBS} 

${TESTER_TARGET}: ${TESTER_OBJS} 
	${CXX} ${LDFLAGS} -o $@ $^ ${LIBS} 

${OBJS}: %.o: %.cpp %.dep 
	${CXX} ${CXXFLAGS} -o $@ -c $< 

${DEPS}: %.dep: %.cpp Makefile 
	${CXX} ${CXXFLAGS} -MM $< > $@ 

clean:
	rm -rf *~ *.o *.dep ${TARGET}

distclean:: clean
