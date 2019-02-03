CC=g++
FLAGS=-std=c++11 -pthread
INCLUDES=-I../gtest/
INCLUDES+=-I../
INCLUDES+=-I../Library/computing/

runArraysTest: 
	$(CC) $(FLAGS) $(INCLUDES) ../gtest/gtest-all.cc arrayTest.c ../Library/computing/array.c -o runTests.o

runAllTests: 
	$(CC) $(FLAGS) $(INCLUDES) data_structures_test.c ../gtest/gtest-all.cc ../Library/computing/data_structures.c -o runTests.o

clean:
	rm *.o









