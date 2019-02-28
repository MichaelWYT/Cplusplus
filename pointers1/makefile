#!/bin/sh
# Makefile

# the C++ compiler
CXX     = g++
CXXVERSION = $(shell g++ --version | grep ^g++ | sed 's/^.* //g')

# options to pass to the compiler
CXXFLAGS = -O0 -g3

ifeq "$(CXXVERSION)" "4.6.3"
	CXXFLAGS += -std=c++0x
else
	CXXFLAGS += -std=c++11
endif

All: all
all: main TextMain


main:	main.cpp Text.o  
	$(CXX) $(CXXFLAGS) main.cpp Text.o -o main

Text.o: Text.cpp Text.h
	$(CXX) $(CXXFLAGS) -c Text.cpp -o Text.o

deepclean: 
	rm -f *~ *.o main TextMain *.exe *.stackdump 

clean:
	-rm -f *~ *.o *.stackdump 
