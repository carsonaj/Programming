CC=g++
FLAGS=-std=c++11 -pthread
GTEST=./../gtest
INCLUDESGTESTS=-I$(GTEST)
INCLUDES=-I./..
INCLUDES+=-I./../Library/computing
GTESTSRC=$(GTEST)/gtest-all.cc
#ALLTESTS=$(wildcard *.c) cant use this cause all files dont compile
ALLTESTS=arrayTest.cpp
RUNALL=runAll.cpp

all: tests

tests: $(ALLTESTS) $(RUNALL) ../Library/computing/array.c
	$(CC) $(FLAGS) $(INCLUDESGTESTS) $(INCLUDES) $(GTESTSRC) $^ -o allTests.o
	
runArraysTest: 
	$(CC) $(FLAGS) $(INCLUDES) ../gtest/gtest-all.cc arrayTest.c \
	../Library/computing/array.c -o runTests.o

runAllTests: 
	$(CC) $(FLAGS) $(INCLUDES) data_structures_test.c \
	../gtest/gtest-all.cc ../Library/computing/data_structures.c -o runTests.o

clean:
	rm -f *.o









