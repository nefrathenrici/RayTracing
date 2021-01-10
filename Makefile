# Simple makefile for compiling main.cpp
CXXFLAGS = -g -std=c++1z -pedantic -Wall -Wextra
CXX = clang++
OBJS := main.o \
		aabb.o \
		bvh.o \
		camera.o \
		hittable.o \
		hittable_list.o \
		material.o \
		ray.o \
		vec3.o		

all: main

main: $(OBJS)
	$(CXX) $(CXXFLAGS) *.o -o main

main.o: *.cpp *.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

aabb.o: aabb.cpp aabb.hpp
	$(CXX) $(CXXFLAGS) -c aabb.cpp

bvh.o: bvh.cpp bvh.hpp
	$(CXX) $(CXXFLAGS) -c bvh.cpp

hittable.o: hittable.cpp hittable.hpp
	$(CXX) $(CXXFLAGS) -c hittable.cpp

hittable_list.o: hittable_list.cpp hittable_list.hpp
	$(CXX) $(CXXFLAGS) -c hittable_list.cpp

camera.o: camera.cpp camera.hpp
	$(CXX) $(CXXFLAGS) -c camera.cpp

material.o: material.cpp material.hpp
	$(CXX) $(CXXFLAGS) -c material.cpp

ray.o: ray.cpp ray.hpp
	$(CXX) $(CXXFLAGS) -c ray.cpp

vec3.o: vec3.cpp vec3.hpp
	$(CXX) $(CXXFLAGS) -c vec3.cpp

clean:
	rm -f *o main