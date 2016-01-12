FLAGS+=-Wall -std=c++11 -I../test

all: Makefile alloc deriv

deriv: Derivative.o 
	$(CXX) Derivative.o -o deriv

alloc: MyAllocator.o
	$(CXX) $(FLAGS) MyAllocator.o -o alloc

MyAllocator.o: MyAllocator.cpp test.h
	$(CXX) -c $(FLAGS) MyAllocator.cpp

Derivative.o: Derivative.cpp test.h
	$(CXX) -c $(FLAGS) Derivative.cpp

clean:
	rm -rf *.o alloc deriv
