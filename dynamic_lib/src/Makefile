all: libmathlib.so call_test

libmathlib.so: mathlib.cc mathlib.h
	g++ -fPIC -shared mathlib.cc -std=c++11 -O2 -o libmathlib.so

call_test: libmathlib.so call_test.cc
	g++ -O2 call_test.cc -Wl,-rpath=. libmathlib.so -o call_test
