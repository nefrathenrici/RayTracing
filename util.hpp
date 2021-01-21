#ifndef UTIL_HPP_
#define UTIL_HPP_

#include <cmath>
#include <limits>
#include <memory>
#include <random>

// Usings
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions
inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double() {
    // Return a random double between in [0,1]
    // Fancy c++!
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double(double min, double max) {
    // Returns a random double in [min,max].
    return min + (max-min)*random_double();
}

inline int random_int(int min, int max) {
    // Returns a random integer in [min,max].
    return static_cast<int>(random_double(min, max+1));
}

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

inline void min_max(double a, double b, double c, double& min, double& max) {
    // Finds min and max of 3 doubles - used for computing bounding box for triangle
    if ( a < b ) {
        min = a;
        max = b;
    } else {
        min = b;
        max = a;
    }
    // 
    if ( c < min )
        min = c;
    else if ( c > max )
        max = c;
}

#endif  // UTIL_HPP_

