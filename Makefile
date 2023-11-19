CXX = g++
CXXFLAGS = -std=c++20 -O3 -Wall -Werror -Wextra -ggdb

project1: main.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY: clean

clean: project1
	rm project1
