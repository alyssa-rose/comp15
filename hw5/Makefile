### Alyssa Rose
### Comp15 HW5
### Makefile for HW5

CXX      = clang++
CXXFLAGS = -std=c++11 -g3 -Wall -Wextra
LDFLAGS  = -g3
DEPS	 = Actor.h Queue.h Stack.h Graph.h LinkedList.h NodeType.h
%.o: %.cpp ${INCLUDES} ${DEPS}
	${CXX} ${CXXFLAGS} -c  -o $@ $<

sixdegrees: main.o SixDegrees.o LinkedList.o Stack.o Queue.o Actor.o Graph.o
	${CXX} ${LDFLAGS} -o sixdegrees main.o SixDegrees.o Graph.o Actor.o LinkedList.o\
	 Stack.o Queue.o
test-graph: test-graph.o Graph.o Actor.o LinkedList.o Stack.o Queue.o
	${CXX} ${LDFLAGS} -o test-graph test-graph.o Graph.o Actor.o LinkedList.o\
	 Stack.o Queue.o

main.o:		main.cpp SixDegrees.h
test-graph.o:	test-graph.cpp Actor.h LinkedList.h Graph.h SixDegrees.h
Actor.o:	Actor.cpp Actor.h LinkedList.h
Graph.o:	Graph.cpp Graph.h Stack.h Queue.h Actor.h
LinkedList.o:	LinkedList.cpp LinkedList.h NodeType.h
SixDegrees.o:	SixDegrees.cpp SixDegrees.h


clean:
	rm -rf sixdegrees *.o *.dSYM

provide:
	provide comp15 hw5 Actor.cpp Actor.h Graph.cpp Graph.h \
			LinkedList.cpp LinkedList.h main.cpp NodeTyp.h \
			Queue.cpp Queue.h README Stack.cpp Stack.h \
			test-graph.cpp
