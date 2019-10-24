CC = g++
FLAGS = -Wall -std=c++14 -O2

testISA: test_isa.cc instruction_set.cc
	$(CC) $(FLAGS) -o $@  $^

instruction_set.cc: instruction_set.h cpuid_x86.h

