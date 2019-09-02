### Alyssa Rose
### Comp15 HW5
### Makefile for Proj2

CXX      = clang++
CXXFLAGS = -std=c++11 -g3 -Wall -Wextra -O2
LDFLAGS  = -g3
DEPS	 = Index.h DirNode.h FSTree.h 
%.o: %.cpp ${INCLUDES} ${DEPS}
	${CXX} ${CXXFLAGS} -c  -o $@ $<

gerp: gerp.o Index.o DirNode.o FSTree.o
	${CXX} ${LDFLAGS} -o gerp gerp.o Index.o DirNode.o FSTree.o
gerp-unittest: gerp-unittest.o Index.o DirNode.o FSTree.o
	${CXX} ${LDFLAGS} -o gerp-unittest gerp-unittest.o Index.o DirNode.o FSTree.o

gerp.o:		gerp.cpp Index.h
gerp-unittest.o:	gerp-unittest.cpp Index.h DirNode.h FSTree.h
Index:	Index.cpp Index.h DirNode.h FSTree.h
DirNode:	DirNode
FSTree:	FSTree.h



clean:
	rm -rf gerp *.o *.dSYM

provide:
	provide comp15 proj2wk2 Makefile README DirNode.h FSTree.h \
	FSTreeTraversal.cpp gerp-unittest.cpp gerp.cpp hashExample.cpp \
	Index.cpp Index.h StringProcessing.cpp testFile.txt 
	