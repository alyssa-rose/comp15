#
# Filename: Makefile
# Part of: Lab assignment "gerp" for Comp 15
# Contains: Makefile for ease of compilation
#

CXX = clang++
CXXFLAGS = -O3 -g3 -Wall -Wextra -std=c++11

gerp: main.o Index-student.o Index.o FSTree.o DirNode.o
	$(CXX) -o $@ $^

%.o: %.cpp $(shell echo *.h)
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -rf Index-student.o main.o gerp *.dSYM
