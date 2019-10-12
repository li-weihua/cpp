CC = g++
FLAGS = -std=c++14 -O2

testISA: test_isa.cc instruction_set.cc
	$(CC) $(FLAGS) -o $@  $^

instruction_set.cc: instruction_set.h x86_cpuid.h

