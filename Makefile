main: main.o
	clang++ -o main -g -std=c++1z -pedantic -Wall -Wextra main.o
main.o: main.cpp vec3.hpp color.hpp hittable.hpp hittable_list.hpp util.hpp sphere.hpp ray.hpp camera.hpp
	clang++ -c -o main.o -g -std=c++1z -pedantic -Wall -Wextra main.cpp