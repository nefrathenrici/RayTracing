// Code adapted from https://raytracing.github.io/books/RayTracingInOneWeekend.html
#include <iostream>

#include "color.hpp"
#include "ray.hpp"
#include "vec3.hpp"

double hit_sphere(const point3& center, double radius, const ray& r) {
    // Detects if the ray r collides with the sphere given by center and radius
    vec3 o_minus_c = r.origin() - center;
    double a = r.direction().length_squared();
    double half_b = dot(o_minus_c, r.direction());
    double c = o_minus_c.length_squared() - radius*radius;
    // Put discrminant together
    double discriminant = half_b*half_b - a*c;
    // If disc < 0, no real roots, doesn't intersect w/ circle
    if (discriminant < 0) {
        return -1.0;
    } else {
        // Quadratic formula - assume unit vector
        return (-half_b - sqrt(discriminant) ) / a;
    }
}

color ray_color(const ray& r) {
    double t = hit_sphere(point3(0,0,-1), 0.5, r);
    if (t > 0.0) {
        // N is normal vector
        vec3 N = unit_vector(r.at(t) - vec3(0,0,-1));
        return 0.5*color(N.x()+1, N.y()+1, N.z()+1);
    }
    vec3 unit_direction = unit_vector(r.direction());
    t = 0.5*(unit_direction.y() + 1.0);
    // Currently hardcodes gradient values to light blue
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main() {
    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera

    auto viewport_height =  2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = static_cast<double>(i) / (image_width-1);
            auto v = static_cast<double>(j) / (image_height-1);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }
    std::cerr << "\nDone.\n";
}
