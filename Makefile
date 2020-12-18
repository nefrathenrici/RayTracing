main: main.o
	clang++ -g -o main main.o
main.o: main.cpp vec3.hpp color.hpp
	clang++ -c -o main.o -g -std=c++1z -pedantic -Wall -Wextra main.cpp