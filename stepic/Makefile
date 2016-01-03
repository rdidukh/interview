FLAGS=-Wall -std=c++11

all: alloc deriv

deriv: Derivative.cpp
	$(CXX) $(FLAGS) Derivative.cpp -o deriv

alloc: MyAllocator.cpp
	$(CXX) $(FLAGS) MyAllocator.cpp -o alloc

clean:
	rm -rf *.o alloc deriv