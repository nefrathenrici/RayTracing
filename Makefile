# Simple makefile for compiling main.cpp
flags = -g -std=c++1z -pedantic -Wall -Wextra
main: main.o
	clang++ -o main $(flags) main.o
main.o: main.cpp vec3.hpp color.hpp hittable.hpp hittable_list.hpp util.hpp sphere.hpp ray.hpp camera.hpp material.hpp aabb.hpp
	clang++ -c -o main.o $(flags) main.cpp