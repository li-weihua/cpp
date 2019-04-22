all: libmathlib.so call_test

libmathlib.so:
	g++ -fPIC -shared mathlib.cc -O2 -o libmathlib.so

call_test: libmathlib.so
	g++ -O2 call_test.cc -Wl,-rpath=. libmathlib.so -o call_test
