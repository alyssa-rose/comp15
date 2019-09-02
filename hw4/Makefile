#
# Makefile for Binary Search Tree
#
# Homework 4 (fall 2018)
#
# Not using -Wextra

CXX      = clang++
CXXFLAGS = -std=c++11 -g3 -Wall -Wextra
LDFLAGS  = -g3

%.o: %.cpp ${INCLUDES}
	${CXX} ${CXXFLAGS} -c  -o $@ $<

hw4: main.o BinarySearchTree.o pretty_print.o
	${CXX} ${LDFLAGS} -o hw4 main.o BinarySearchTree.o pretty_print.o

unittests: CXXFLAGS += -isystem /usr/sup/include
unittests: LDLIBS   += -lpthread -lgtest
unittests: LDFLAGS  += -L/usr/sup/lib
unittests: runalltests.o BinarySearchTree-unittest.o pretty_print.o \
				BinarySearchTree.o
		${CXX}  -o $@ $^ ${LDFLAGS} ${LDLIBS}


main.o:              main.cpp BinarySearchTree.h 
BinarySearchTree.o:  BinarySearchTree.cpp BinarySearchTree.h
pretty_print.o:      pretty_print.cpp BinarySearchTree.h
runalltests.o:		 runalltests.cpp

clean:
	rm -rf hw4 *.o *.dSYM

provide:
	provide comp15 hw4 main.cpp BinarySearchTree.cpp BinarySearchTree.h \
	        pretty_print.cpp README Makefile BinarySearchTree-unittest.cpp \
	        runalltests.cpp

