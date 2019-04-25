inc = $(shell python3 -m pybind11 --includes)
flags = -O3 -Wall -fPIC -shared -std=c++11 
example:
	g++ ${flags} ${inc} example.cpp -o example.so
