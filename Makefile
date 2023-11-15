CXX = g++
CXXFLAGS = -std=c++20 -O0 -Wall -Werror -Wextra

project1: main.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY: clean

clean: project1
	rm project1
