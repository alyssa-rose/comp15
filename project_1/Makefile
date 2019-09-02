### Alyssa Rose
### Comp15 Proj1
### Makefile for Grep

CXX      = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra -g3
INCLUDES  = Grep.h

%.o: %.cpp ${INCLUDES}
	${CXX} ${CXXFLAGS} -c  -o $@ $<

SeqMatch: SeqMatch.o Grep.o 
	${CXX} ${LDFLAGS} -o SeqMatch SeqMatch.o Grep.o 

clean:
	rm -rf SeqMatch *.o *.dSYM

provide:
	provide comp15 proj1wk2 SeqMatch.cpp Grep.cpp Grep.h \
			README Makefile Grep-unittest.cpp
