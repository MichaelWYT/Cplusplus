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
all: main PointMain LineMain PLCMain

main: main.cpp Point.o Line.o PLContainer.o
	$(CXX) $(CXXFLAGS) main.cpp Point.o Line.o PLContainer.o -o main		

Point.o: Point.cpp Point.h 
	$(CXX) $(CXXFLAGS) -c Point.cpp -o Point.o

Line.o:	Line.cpp Line.h
	$(CXX) $(CXXFLAGS) -c Line.cpp -o Line.o

PLContainer.o: PLContainer.cpp PLContainer.h
	$(CXX) $(CXXFLAGS) -c PLContainer.cpp -o PLContainer.o

PointMain:	PointMain.cpp Point.o PointTester.o TesterBase.o
	$(CXX) $(CXXFLAGS) PointMain.cpp Point.o PointTester.o TesterBase.o -o PointMain

LineMain:	LineMain.cpp Line.o LineTester.o TesterBase.o Point.o
	$(CXX) $(CXXFLAGS) LineMain.cpp Line.o LineTester.o TesterBase.o Point.o -o LineMain

PLCMain:   PLCMain.cpp Point.o Line.o PLContainer.o PLContainerTester.o TesterBase.o
	$(CXX) $(CXXFLAGS) PLCMain.cpp Point.o Line.o  PLContainer.o PLContainerTester.o TesterBase.o -o PLCMain

PointTester.o: PointTester.cpp PointTester.h
	$(CXX) $(CXXFLAGS) -c PointTester.cpp -o PointTester.o

LineTester.o: LineTester.cpp LineTester.h
	$(CXX) $(CXXFLAGS) -c LineTester.cpp -o LineTester.o

PLContainerTester.o: PLContainerTester.cpp PLContainerTester.h
	$(CXX) $(CXXFLAGS) -c PLContainerTester.cpp -o PLContainerTester.o

TesterBase.o: TesterBase.cpp TesterBase.h
	$(CXX) $(CXXFLAGS) -c TesterBase.cpp -o TesterBase.o

deepclean: 
	rm -f *~ *.o main PointMain LineMain PLCMain *.exe *.stackdump 

clean:
	-rm -f *~ *.o *.stackdump
