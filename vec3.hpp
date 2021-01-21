// Code for the basic vector class. Will be used for rays, colors, points, and math.

#ifndef VEC3_HPP_
#define VEC3_HPP_

#include <cmath>
#include <iostream>
#include "util.hpp"

using std::sqrt;

class vec3 {
    public:
        // x,y,z coordinate
        double e[3];

        // Constructors
        vec3();
        vec3(double e0, double e1, double e2);

        double x() const;
        double y() const;
        double z() const;

        // Negation
        vec3 operator-() const;

        // Indexing
        double operator[](int i) const;

        // Referencing
        double& operator[](int i);

        vec3& operator+=(const vec3 &v);

        vec3& operator*=(const double t);

        vec3& operator/=(const double t);

        double length() const;

        double length_squared() const;

        inline static vec3 random() {
                return vec3(random_double(), random_double(), random_double());
            }

        inline static vec3 random(double min, double max) {
            return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
        }

        // Helper function to avoid NaNs
        bool near_zero() const;
};

// Type aliases for vec3
using point3 = vec3;   // 3D point
using color = vec3;    // RGB color

// vec3 Utility Functions

// Print
inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

// Vector addition
inline vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

// Vector subtraction
inline vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

// Vector multiplication
inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

// Scalar multiplication
inline vec3 operator*(double t, const vec3 &v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

// Scalar multiplication (commutative)
inline vec3 operator*(const vec3 &v, double t) {
    return t * v;
}

// Scalar division
inline vec3 operator/(vec3 v, double t) {
    return (1/t) * v;
}

// Dot product
inline double dot(const vec3 &u, const vec3 &v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

// Cross product
inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

// Unit vector
inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}

// Random vec3 for diffuse material
inline vec3 random_in_unit_sphere() {
    while (true) {
        vec3 p = vec3::random(-1, 1);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

// Random unit vector
inline vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

inline vec3 random_in_hemisphere(const vec3& normal) {
    vec3 in_unit_sphere = random_in_unit_sphere();
    if (dot(in_unit_sphere, normal) > 0.0)  // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}

// Reflected vector
inline vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2*dot(v, n)*n;
}

// Refraction - implementation of Snell's Law
inline vec3 refract(const vec3& uv, const vec3& n, double eta_over_eta_prime) {
    auto cos_theta = fmin(dot(-uv, n), 1.0);
    vec3 r_out_perp =  eta_over_eta_prime * (uv + cos_theta*n);
    vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

inline vec3 random_in_unit_disk() {
    while (true) {
        auto p = vec3(random_double(-1, 1), random_double(-1, 1), 0);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

inline double determinant3(vec3 c0, vec3 c1, vec3 c2) {
    // 3x3 determinant of 3 column vec3s - using diagonal method
    return  (c0.x() *c1.y() * c2.z()) +
            (c1.x() *c2.y() * c0.z()) +
            (c2.x() *c0.y() * c1.z()) -
            (c2.x() *c1.y() * c0.z()) -
            (c0.x() *c2.y() * c1.z()) -
            (c1.x() *c0.y() * c2.z());
}

#endif  // VEC3_HPP_
