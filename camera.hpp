#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "util.hpp"
#include "ray.hpp"

// Class controlling the camera. 
/* Currently support the following features:
    * Aspect ratio
    * View location and positioning
    * Vertical field of view
    * Aperture
    * Focal length
    */

class camera {
    public:
        camera(
            point3 lookfrom,
            point3 lookat,
            vec3   vup,
            double vfov,  // vertical field-of-view in degrees
            double aspect_ratio,
            double aperture,
            double focus_dist
        );

        ray get_ray(double s, double t) const;

    private:
        point3 origin;
        point3 lower_left_corner;
        vec3 horizontal;
        vec3 vertical;
        vec3 u, v, w;
        double lens_radius;
};

#endif  // CAMERA_HPP_
