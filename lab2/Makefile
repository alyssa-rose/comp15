#
#  Makefile
#  COMP15
#  Fall 2018
#
#  Makefile for the planet-driver, LinkedList and Planet
#


CC = clang++
CFLAGS = -Wall -Wextra -c
DEPS = Planet.h LinkedList.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

planet-driver: planet-driver.o Planet.o LinkedList.o
	$(CC) -o planet-driver planet-driver.o Planet.o LinkedList.o

clean:
	rm -f *.o core* *~ planet-driver
