CC=g++
FLAGS=-std=c++11 -pthread
INCLUDES=-I../gtest/
INCLUDES+=-I../Library/computing/



runAllTests: 
	$(CC) $(FLAGS) $(INCLUDES) data_structures_test.c ../gtest/gtest-all.cc ../Library/computing/data_structures.c -o runTests.o

clean:
	rm runTests.o









