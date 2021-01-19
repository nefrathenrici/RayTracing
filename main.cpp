// Code adapted from https://raytracing.github.io/books/RayTracingInOneWeekend.html
#include <iostream>
#include "camera.hpp"
#include "color.hpp"
#include "hittable_list.hpp"
#include "material.hpp"
#include "sphere.hpp"
#include "ray.hpp"
#include "util.hpp"

color ray_color(const ray& r, const hittable& world, size_t depth) {
    hit_record rec;
    if (depth <= 0)
        return color(0, 0, 0);
    // t = 0.001 instead of 0 to deal with shadow acne
    if (world.hit(r, 0.001, infinity, rec)) {
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth-1);
        return color(0,0,0);
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    // Hardcoded blue gradient
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}
hittable_list test_scene() {
    hittable_list world;

    // Test scene
    auto ground_material = make_shared<metal>(color(0.5, 0.5, 0.5),0.0);
    auto sphere_material_b = make_shared<lambertian>(color(0.5, 0.5, 0.8));
    auto sphere_material_g = make_shared<metal>(color(0.5, 0.8, 0.5),0.0);
    auto sphere_material_r = make_shared<metal>(color(0.8, 0.5, 0.5),0.0);

    world.add(make_shared<sphere>(point3( 0.0, -1000.5, 0.0), 1000.0, ground_material));
    world.add(make_shared<sphere>(point3(-1.5,0,0),0.5,sphere_material_r));
    world.add(make_shared<sphere>(point3(-0.5,0,0),0.5,sphere_material_g));
    world.add(make_shared<sphere>(point3(0.5,0,0),0.5,sphere_material_b));
    world.add(make_shared<sphere>(point3(1.5,0,0),0.5,make_shared<dielectric>(0.7)));
    return world;
}

int main() {

    // Image

    const auto aspect_ratio = 3.0 / 2.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 50;
    const int max_depth = 50;

    // World

    auto world = test_scene();

    // Camera

    point3 lookfrom(-6,3,-6);
    point3 lookat(0,0,0);
    vec3 vup(0, 1, 0);
    auto dist_to_focus = (lookfrom-lookat).length();
    auto aperture = 0.2;

    camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j+1 << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
                        color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_double()) / (image_width-1);
                auto v = (j + random_double()) / (image_height-1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }
    std::cerr << "\nDone.\n";
}
