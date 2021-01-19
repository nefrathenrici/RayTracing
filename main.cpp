// Code adapted from https://raytracing.github.io/books/RayTracingInOneWeekend.html
#include <iostream>
#include "camera.hpp"
#include "color.hpp"
#include "hittable_list.hpp"
#include "material.hpp"
#include "sphere.hpp"
#include "ray.hpp"
#include "util.hpp"
color ray_color(const ray& r, const color& background, const hittable& world, int depth) {
    hit_record rec;

    // Recursion depth reached
    if (depth <= 0)
        return color(0,0,0);

    // If the ray hits nothing, return the background color.
    if (!world.hit(r, 0.001, infinity, rec))
        return background;

    ray scattered;
    color attenuation;
    color emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);

    // If light is hit, return emitted light
    if (!rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        return emitted;

    // Hit object, return emitted and scattered light - recursive
    return emitted + attenuation * ray_color(scattered, background, world, depth-1);
}

// Scenes

hittable_list test_scene() {
    hittable_list world;
    // Test scene
    auto ground_checker = make_shared<checker>(
                                            color(0.2, 0.2, 0.2),
                                            color(0.7, 0.7, 0.7));
    world.add(make_shared<sphere>(
                                point3( 0.0, -1000.5, 0.0), 
                                1000.0, 
                                make_shared<lambertian>(ground_checker)));

    auto sphere_material_b = make_shared<metal>(
                                                color(0.3,0.3, 0.9),
                                                0.0);
    auto sphere_material_g = make_shared<metal>(
                                                color(0.3, 0.9, 0.3),0.5);
    auto sphere_material_r = make_shared<lambertian>(
                                                    color(0.9, 0.3, 0.3));

    world.add(make_shared<sphere>(point3(-1.5,0,0),0.5,sphere_material_r));
    world.add(make_shared<sphere>(point3(-0.5,0,0),0.5,sphere_material_g));
    world.add(make_shared<sphere>(point3(0.5,0,0),0.5,sphere_material_b));

    world.add(make_shared<sphere>(point3(1.5,0,0),0.5,make_shared<dielectric>(0.7)));

    world.add(make_shared<sphere>(point3(0,6,0),4,make_shared<diffuse_light>(color(2,2,2))));

    return world;
}

// Render
int main() {

    // Camera and Render Settings
    const auto aspect_ratio = 3.0 / 2.0;
    const int image_width = 300;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 1000;
    const int max_depth = 50;

    // Prep world
    hittable_list world;
    point3 lookfrom;
    point3 lookat;
    vec3 vup;
    double dist_to_focus;
    double aperture;
    color background;

    switch (0) {
        // Just one scene currently
        default:
            world = test_scene();
            // Camera
            lookfrom = point3(-6,3,-6);
            lookat = point3(0,0,0);
            vup = vec3(0, 1, 0);
            dist_to_focus = (lookfrom-lookat).length();
            aperture = 0.2;
            background = color(0.5,0.5,0.5);
        
    }    

    // Set camera
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
                pixel_color += ray_color(r, background, world, max_depth);
            }
            // std::cerr << pixel_color << "\n";
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }
    std::cerr << "\nDone.\n";
}
