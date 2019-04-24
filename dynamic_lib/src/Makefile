all: libmathlib.so call_test dl_test

libmathlib.so: mathlib.cc mathlib.h
	g++ -fPIC -shared mathlib.cc -std=c++11 -O2 -o libmathlib.so

call_test: libmathlib.so call_test.cc mathlib.h
	g++ -O2 call_test.cc -Wl,-rpath=. libmathlib.so -o call_test

dl_test: libmathlib.so dl_test.cc mathlib.h
	g++ -O2 dl_test.cc -ldl -o dl_test

clean:
	-rm libmathlib.so call_test dl_test
