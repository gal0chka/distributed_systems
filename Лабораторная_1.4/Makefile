CXX ?= clang++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -Wpedantic -msse4.1

ifeq ($(shell uname -s)-$(shell uname -m),Darwin-arm64)
CXXFLAGS += -arch x86_64
endif

.PHONY: all test run clean

all: lab_1_4

lab_1_4: main.cpp lab.cpp lab.hpp input_reader.hpp
	$(CXX) $(CXXFLAGS) main.cpp lab.cpp -o $@

tests: tests.cpp lab.cpp lab.hpp
	$(CXX) $(CXXFLAGS) tests.cpp lab.cpp -o $@

test: tests
	./tests

run: lab_1_4
	./lab_1_4 data/input_const.txt result.txt

clean:
	rm -f lab_1_4 tests result.txt

