#CXX=g++

TRAINER_SRCS := trainer.cpp ImageRepository.cpp rgb_to_hsv.cpp ImageClass.cpp Image.cpp util.cpp ClassLabelsFile.cpp
TRAINER_OBJS := ${TRAINER_SRCS:.cpp=.o} 
TRAINER_DEPS := ${TRAINER_SRCS:.cpp=.dep} 

RECOGNIZER_SRCS := recognizer.cpp Image.cpp rgb_to_hsv.cpp ClassLabelsFile.cpp
RECOGNIZER_OBJS := ${RECOGNIZER_SRCS:.cpp=.o} 
RECOGNIZER_DEPS := ${RECOGNIZER_SRCS:.cpp=.dep} 

OBJS    := $(sort ${TRAINER_OBJS} ${RECOGNIZER_OBJS})
DEPS    := $(sort ${TRAINER_DEPS} ${RECOGNIZER_DEPS})
XDEPS   := $(wildcard ${TRAINER_DEPS}) $(wildcard ${RECOGNIZER_DEPS}) 

TRAINER_TARGET    := trainer
RECOGNIZER_TARGET := recognizer
TARGETS           := ${TRAINER_TARGET} ${RECOGNIZER_TARGET}

# Determine whether to use the -mt suffix or not for boost libraries
ifneq ($(wildcard /usr/{local,}/lib/libboost_filesystem-mt.*),)
BOOST_SUFFIX=-mt
else
BOOST_SUFFIX=
endif


LIBS     = -lopencv_core \
		   -lopencv_highgui \
		   -lopencv_imgproc \
		   -lopencv_ml \
		   -lboost_filesystem${BOOST_SUFFIX} \
		   -lboost_system${BOOST_SUFFIX}
CXXFLAGS = -O2 -Wall
LDFLAGS  = ${XLDFLAGS}

.PHONY: all clean distclean test
all:: ${TARGETS} 

ifneq (${XDEPS},) 
include ${XDEPS} 
endif 

${TRAINER_TARGET}: ${TRAINER_OBJS} 
	${CXX} ${LDFLAGS} -o $@ $^ ${LIBS} 

${RECOGNIZER_TARGET}: ${RECOGNIZER_OBJS} 
	${CXX} ${LDFLAGS} -o $@ $^ ${LIBS} 

${OBJS}: %.o: %.cpp %.dep 
	${CXX} ${CXXFLAGS} -o $@ -c $< 

${DEPS}: %.dep: %.cpp Makefile 
	${CXX} ${CXXFLAGS} -MM $< > $@ 

clean:
	rm -rf *~ *.o *.dep ${TARGET}

distclean:: clean
