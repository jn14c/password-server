all: proj5.x sproj5.x
CC=gcc
CXX=g++
CXXFLAGS=-std=c++11 -Wall -pedantic -lncurses -lcrypt

proj5.x: proj5.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

sproj5.x: sproj5.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

.SUFFIXES: .x

.PHONY : clean

clean:
	rm -f *.x


